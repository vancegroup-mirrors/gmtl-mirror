/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: pfAppCore.cpp,v $
 * Date modified: $Date: 2002-01-18 20:43:10 $
 * Version:       $Revision: 1.1.1.1 $
 * -----------------------------------------------------------------
 *
 *********************************************************** ggt-head end */
/*************************************************************** ggt-cpr beg
*
* GGT: The Generic Graphics Toolkit
* Copyright (C) 2001,2002 Allen Bierbaum 
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*
 ************************************************************ ggt-cpr end */
// file: pfAppCore.cpp
// --------------
//
//  This is the core to hold a performer based applicaiton object for us
//

// general includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <getopt.h> // for cmdline handler
#include <iostream.h>

// X Window includes
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

// Performer includes
#include <Performer/pf/pfChannel.h>
#include <Performer/pf/pfDCS.h>
#include <Performer/pf/pfLightSource.h>
#include <Performer/pf/pfGeode.h>
#include <Performer/pr/pfTexture.h>
#include <Performer/pr/pfGeoSet.h>
#include <Performer/pf/pfScene.h>
#include <Performer/pr/pfMemory.h>
#include <Performer/pr/pfMaterial.h>

#include <Performer/pfutil.h>
#include <Performer/pfdu.h>
#include <Performer/pfui/pfiXformer.h>
#include <Performer/pfui.h>
#include <Performer/pfui/pfiPick.h>

#include <pfObbTreeApp.h>

pfObbTreeApp* theApp;

/******************************************************************************
*           Defines and Typedefs
******************************************************************************
*/


// Panel Widget Control Tokens
enum PanelControlToken {
    CTL_RESET_ALL=1,
    CTL_REPOSITION,
    CTL_QUIT,
    CTL_MODEL,
    CTL_DIAGS,
    CTL_TREE,
    CTL_WIREFRAME,
    CTL_OUTPUT_SCENE,
    CTL_CUBLET_SIZE,
    CTL_SURF_THRESHOLD,
    CTL_NORMALS
    };

struct PanelData
{

};

// SharedData:
// structure that resides in shared memory so that the
// application, cull, and draw processes can access it.
//
struct SharedData
{
    // main channel stuff
    pfChannel     *chan;
    pfVec3     startXYZ;
    float      sceneSize;
    int        drawStats;
    int        exitFlag;
    pfLightSource *sun;    // sun light source

    // Input handling strPanelItemDatauctures
    int        input;      // PFUINPUT_GL or PFUINPUT_X
    pfuMouse      mouse;      // mouse structure
    pfuEventStream   events;     // event structure

    // flight model and collision detection sructures
    pfScene    *scene;
    pfGeoState*      globalSceneState;   // Global Scene state
    pfDCS      *sceneDCS;  // DCS for trackball interface
    pfCoord    viewCoord;  // current view position, direction
    pfCoord    initView;   // initial view position, direction
    float      near;    // near clipping plane
    float      far;     // far clipping plane
    pfiXformer    *xformer;   // interactive movement model
    int        xformerModel;  // Fly, Drive, or Trackball
    int        collideMode;   // collision & terrain following flag

    // flags for GUI
    int        updateChannels;
    int        gui, redraw, guiDirty;
    pfuPanel      *guiPanel;
    pfuWidget     *wResetAll, *wKillGUI, *wPosXYZ, *wStats, *wTree, *wFModel, *wWireframe;
    pfuWidget     *wNormals, *wCubletSize, *wSurfThreshold;

   // ---- Object stuff --- //
    pfGeoSet*  theObject;
    pfGeoState*   theState;
    pfMaterial* theMaterial;

   // Picking Data
    pfiPick*      pick;
};

/******************************************************************************
*           Static Declarations
******************************************************************************/

// shared memory handle
static SharedData *Shared=0;

// X control variables
static int XInput = PFUINPUT_X;
static int WinXOrigin = 100, WinYOrigin = 100;
static int WinXSize = 1000, WinYSize = 800;

// process control variables
static int ProcSplit = PFMP_APPCULLDRAW;

static void CullChannel(pfChannel *chan, void *data);
static void DrawChannel(pfChannel *chan, void *data);
static void OpenPipeWin(pfPipeWindow *pw);
static pfuPanel *InitPanel(void);
static void ProcessInputIO(void);
static void PanelControl(pfuWidget *w);
static void resetPosition(void);
static void KillGUI(pfuWidget *w);
static void Usage(void);
static void InitXformer(void);
static void IsectFunc(void *data);
static void UpdateView(pfChannel *chan, pfScene *scene);
static void updateGUIViewMsg(pfCoord *viewpt);
static void xformerModel(int model, int collideMode);

void updateObjectMaterials();


// Pick Callback routine
static int PickHitCB(pfiPick* pick, void* data);

// DRaw callbacks
int PostDrawSurface(pfTraverser* trav, void* data);
int PreDrawSurface(pfTraverser* trav, void* data);

/******************************************************************************
*            Main and Commandline Processing
******************************************************************************
*/

//
//      Usage() -- print usage advice and exit. This procedure
// is executed in the application process.
//

char OptionStr[] = "m:p:x?";

static void
Usage (void)
{
    fprintf(stderr, "Usage: myviewer file.ext \n");
    exit(1);
}

// --- Update the

void updateObjectMaterials()
{
    //Shared->theMaterial->setColorMode(PFMTL_BOTH, PFMTL_CMODE_OFF);
    //Shared->theMaterial->setColor(PFMTL_AMBIENT, pfuGetWidgetValue(Shared->objMat.ambient[0]), pfuGetWidgetValue(Shared->objMat.ambient[1]), pfuGetWidgetValue(Shared->objMat.ambient[2]));
    //Shared->theMaterial->setColor(PFMTL_DIFFUSE, pfuGetWidgetValue(Shared->objMat.diffuse[0]), pfuGetWidgetValue(Shared->objMat.diffuse[1]), pfuGetWidgetValue(Shared->objMat.diffuse[2]));
    //Shared->theMaterial->setColor(PFMTL_EMISSION, pfuGetWidgetValue(Shared->objMat.emission[0]), pfuGetWidgetValue(Shared->objMat.emission[1]), pfuGetWidgetValue(Shared->objMat.emission[2]));
    //Shared->theMaterial->setColor(PFMTL_SPECULAR, pfuGetWidgetValue(Shared->objMat.specular[0]), pfuGetWidgetValue(Shared->objMat.specular[1]), pfuGetWidgetValue(Shared->objMat.specular[2]));
    //Shared->theMaterial->setShininess(pfuGetWidgetValue(Shared->objMat.shininess));
    //Shared->theMaterial->setAlpha(pfuGetWidgetValue(Shared->objMat.alpha));
}



//
// main() -- program entry point. this procedure
// is executed in the application process.
//
int
main (int argc, char *argv[])
{
   //int         arg;
   float       far = 10000.0f;

   theApp = pfObbTreeApp::instance();   // Get the application
   if(argc > 1)
      theApp->setUserFilename(argv[1]);

   theApp->init();

   pfNotifyLevel(PFNFY_DEBUG);      // Set Error handling level
   pfInit();
   pfFilePath(".:/usr/share/Performer/data:/usr/demos/data/textures");

   theApp->preForkInit();

   pfMultiprocess(ProcSplit);


   // allocate shared before fork()'ing parallel processes
   // so that all processes have will the correct Shared address
   //
   Shared = (SharedData*)pfCalloc(1, sizeof(SharedData), pfGetSharedArena());

   if (Shared == NULL)
   {
      cerr << "Shared data allocated a null" << endl;
      exit(0);
   }

   // init shared memory structures
   Shared->xformerModel          = PFITDF_TRACKBALL;
   Shared->input                 = XInput;
   Shared->collideMode           = PF_ON;
   Shared->gui                   = 1; // enable gui
   Shared->updateChannels        = 1;
   Shared->guiDirty = Shared->redraw = 1;
   Shared->pick = new pfiPick;                        // Create the pick object
   Shared->pick->setHitFunc(PickHitCB, NULL);         // Set call back with no data passed
   Shared->pick->setMode(PFIP_MODE_PICK, PFPK_M_NEAREST);

   // initiate multi-processing mode set in pfMultiprocess call
   // FORKS HAPPEN HERE !!!
   // But first load all dso's
   if (argc > 1)
      pfdInitConverter(argv[1]);     // Load DSO for the loader for file.ext

   pfConfig();

   // init shared mem for utility libraries
   pfuInitUtil();
   pfiInit();


   // Initialize input structure (X or GL) for mouse and event inputs
   // then Open and configure full screen GL or GLX window.
   //

   // Configure window for the pipe
   pfPipe *p = pfGetPipe(0);
   pfPipeWindow *pw = new pfPipeWindow(p);
   pw->setName(argv[0]);
   pw->setOriginSize(WinXOrigin, WinYOrigin,
                     WinXOrigin +  WinXSize, WinYOrigin +  WinYSize);
   if (Shared->input == PFUINPUT_X)
      pw->setWinType(PFPWIN_TYPE_X);

   pw->setConfigFunc(OpenPipeWin);
   pw->config();

   pfFrame();

   pfuInitGUI(pw);
   pfuInitInput(pw, Shared->input);

   //
   // App Process Setup
   //
   pfScene *scene = new pfScene;       // Declare pfScene Object
   Shared->sceneDCS = new pfDCS;       // Declare a sceneDCS
   scene->addChild(Shared->sceneDCS);     // Add the DCS to the top of tree

   //// Create the scene graphy \\\\\
   // Init fluid stuff
   theApp->apiInit();
   theApp->initScene();
   Shared->sceneDCS->addChild(theApp->getScene());

   // Setup Global State
   pfGeoState*   globalState = new pfGeoState;
   scene->setGState(globalState);
   Shared->globalSceneState = globalState;
   globalState->setMode(PFSTATE_ENWIREFRAME, PFTR_OFF);  // Default to Wireframe off

   // Set intersection callback.
   pfIsectFunc(IsectFunc);
   pfuCollideSetup(scene, PFUCOLLIDE_STATIC, 0xffffffff);      // do intersection setup

   Shared->scene = scene;

   // Create pfChannels and assign draw callback functions.
   // Channels will automatically be assigned to the first created window
   // on the pfPipe.
   //

   pfChannel *chan = new pfChannel(p);
   Shared->chan = chan;

   chan->setTravFunc(PFTRAV_CULL, CullChannel);
   chan->setTravFunc(PFTRAV_DRAW, DrawChannel);
   chan->setScene(scene);
   chan->setNearFar(0.1f, far);
   // vertical FOV is matched to window aspect ratio
   chan->setFOV(45.0f, -1.0f);

   // Intialize Pick channels
   Shared->pick->addChan(chan);    // Add channel
   Shared->pick->setupChans();      // Setup the channel stuff ???

   // Initialize sun - create a light source in the "south-west" (QIII)
   Shared->sun = new pfLightSource;
   Shared->sun->setPos(-0.3f, -0.3f, 1.0f, 0.0f);
   Shared->scene->addChild(Shared->sun);

   pfFrameStats *stats = chan->getFStats();
   stats->setClass(PFSTATS_ENGFX, PF_ON);

   // set up scene bounding box and initial viewing position
   {
      float sceneSize;
      pfVec3 view;
      // Set initial view to be "in front" of scene

      // view point at center of bbox
      // determine extent of scene's geometry
      pfBox bbox;
      pfuTravCalcBBox(scene, &bbox);

      // find max dimension
      sceneSize = PF_MAX2(PF_MAX2(bbox.max[PF_X] - bbox.min[PF_X], bbox.max[PF_Y] - bbox.min[PF_Y]), bbox.max[PF_Z] - bbox.min[PF_Z]);
      sceneSize = PF_MIN2(sceneSize, 0.5f * far);
      Shared->sceneSize = sceneSize;
      view.add(bbox.min, bbox.max);
      Shared->viewCoord.xyz.scale(0.5f, view);

      // offset so all is visible
      Shared->viewCoord.xyz[PF_Y] -=      sceneSize;
      Shared->viewCoord.xyz[PF_Z] += 0.25f*sceneSize;

      Shared->viewCoord.hpr.set(0.0f, 0.0f, 0.0f);
      chan->setView(Shared->viewCoord.xyz,
                    Shared->viewCoord.hpr);
      Shared->initView = Shared->viewCoord;
   }
   Shared->startXYZ.copy(Shared->viewCoord.xyz);

   // Setup view ports to initially display the panel
   Shared->chan->setViewport(0.0f, 1.0f, 0.25f, 1.0f);
   pfuGUIViewport(0.0f, 1.0f, 0.0f, 0.25f);
   Shared->guiPanel = InitPanel();
   pfuEnablePanel(Shared->guiPanel);

   // Initialize channel viewing model for interactive motion
   InitXformer();

   pfEnable(PFEN_TEXTURE);
   // main simulation loop
   while (!Shared->exitFlag)
   {
      // wait until next frame boundary
      pfSync();
      theApp->postFrame();

      //
      // All latency critical processing should be done here. This is
      // typically the viewing position.
      // One should also read latency critical devices here.
      //
      pfuGetMouse(&Shared->mouse);      // Copy data into the mouse structure
      //pfNotify(PFNFY_DEBUG, PFNFY_PRINT,   // Output current mouse location
      //      "Mouse: Pos: %d, %d\n",
      //      Shared->mouse.xpos, Shared->mouse.ypos);
      if (Shared->mouse.flags & PFUDEV_MOUSE_LEFT_DOWN)
      {
         pfNotify(PFNFY_DEBUG, PFNFY_PRINT, "Left Button pressed\n");
         Shared->pick->doPick(Shared->mouse.xpos, Shared->mouse.ypos);   // Pick at x,y
      }
      UpdateView(Shared->chan, Shared->scene);


      theApp->preFrame();
      pfFrame();     // Trigger traversals
      theApp->intraFrame();

      // Get snapshot of event/key queues
      pfuGetEvents(&Shared->events);
      ProcessInputIO();

      // Update the channels with any changes from the previous frame
      if (Shared->updateChannels)
      {
         if (Shared->gui)
         {
            float foo, top;

            Shared->redraw = Shared->guiDirty = 1;
            pfuEnableGUI(TRUE);
            pfuGetGUIViewport(&foo, &foo, &foo, &top);
            Shared->chan->setViewport(0.0f, 1.0f, top, 1.0f);
         }
         else
         {
            pfuEnableGUI(FALSE);
            Shared->chan->setViewport(0.0f, 1.0f, 0.0f, 1.0f);
         }
         Shared->guiDirty = Shared->updateChannels = 0;
      }
      else if (Shared->gui)
      {
         updateGUIViewMsg(&(Shared->viewCoord));
         pfuUpdateGUI(&(Shared->mouse));
      }
   }

   theApp->exit();

   // exit GUI and print avg time to draw GUI - optional
   pfuExitGUI();
   // Exit from libpfutil and remove shared mem arenas
   pfuExitUtil();
   pfuExitInput();

   // terminate cull and draw processes (if they exist)
   pfExit();

   // exit to operating system
   exit(0);
   return 0;
}

static void
InitXformer(void)
{
    Shared->xformer = (pfiXformer *)pfiNewTDFXformer(pfGetSharedArena());
    Shared->xformer->setAutoInput(Shared->chan, &Shared->mouse, &Shared->events);
    Shared->xformer->setNode(Shared->scene);
    Shared->xformer->setAutoPosition(Shared->chan, Shared->sceneDCS);
    Shared->xformer->setResetCoord(&Shared->initView);
    xformerModel(Shared->xformerModel, Shared->collideMode);

}

static void
IsectFunc(void *)
{
//    pfiCollideXformer(Shared->xformer);
}


/******************************************************************************
*            App Viewing Model Routines
******************************************************************************
*/

//
// Thes routines use the viewing and tranformation utilities in
// libpfutil to implement several fiewing modes: drive, fly, and trackball.
//

static void
xformerModel(int model, int collideMode)
{
    static int    oldModel = -1, oldCollMode = -1;

    if ((model == oldModel && oldCollMode == collideMode) || !Shared->xformer)
   return;

    if (oldModel != model)
   Shared->xformer->selectModel(model);

    /* Collide with objects in scene */
    if (oldCollMode != collideMode)
    {
   if (collideMode == PF_ON)
       Shared->xformer->enableCollision();
   else
       Shared->xformer->disableCollision();
   oldCollMode = collideMode;
    }
}

//
// Update the current view
//
static void
UpdateView(pfChannel *, pfScene *)
{
    pfiUpdateXformer(Shared->xformer);
    Shared->xformerModel = Shared->xformer->getCurModelIndex();

    /* if have moving-eyepoint motion model, update eyepoint */
    if (Shared->xformer->getCurModel()->isOfType(
       pfiInputXformTravel::getClassType()))
    {
   Shared->xformer->getCoord(&Shared->viewCoord);
    }
}


//
// Reset view to original XYZ position and HPR Euler angles
//
static void
resetPosition(void)
{
    Shared->xformer->stop();
    Shared->xformer->resetPosition();
}


/******************************************************************************
*            App Input Handling
******************************************************************************
*/

static void
ProcessInputIO(void)
{
   int i,j,key;
   int dev, numDevs;
   //int val;
   pfuEventStream *pfevents;

   pfevents = &(Shared->events);

   numDevs = pfevents->numDevs;
   for (j=0; j < numDevs; j++)
   {
      dev = pfevents->devQ[j];
      //val = pfevents->devVal[j];
      if (pfevents->devCount[dev] > 0)
      {
         switch (dev)
         {
         case PFUDEV_REDRAW:
            // worst case in APP_CULL_DRAW mode it takes 3 frames to
            // propagate new window size back down to draw process.
            //
            Shared->redraw = 3;
            pfuRedrawGUI();
            pfevents->devCount[dev] = 0; // mark device done
            break;

         case PFUDEV_WINQUIT:
            Shared->exitFlag = 1;
            pfevents->devCount[dev] = 0; // mark device done
            break;

            // Main Keyboard
         case PFUDEV_KEYBD:
            for (i=0; i<pfevents->numKeys; i++)
            {
               key = pfevents->keyQ[i];
               if (pfevents->keyCount[key])
               { // key was pressed count times
                  switch (key)
                  {
                  case 27: // ESC
                     Shared->exitFlag = 1;
                     break;
                  case 'g':
                  case 'G':
                     Shared->drawStats = !Shared->drawStats;
                     pfuWidgetValue(Shared->wStats,
                                    Shared->drawStats);
                     break;
                  case 'r':
                  case 'R':
                     resetPosition();
                     break;
                  case ' ':
                     Shared->xformer->stop();
                     break;
                  default:
                     break;
                  }
               }
            }
            // XXX this is very important or else future keybd events
            // will be lost !!!
            //
            pfevents->devCount[dev] = 0; // mark device done
            break;
         case PFUDEV_F1KEY:
            Shared->gui = !Shared->gui;
            pfuWidgetValue(Shared->wKillGUI, Shared->gui);
            Shared->updateChannels = 1;
            pfevents->devCount[dev] = 0; // mark device done
            break;
         } // switch on device
      } // if have device
   } // for each device
   pfevents->numDevs = 0;
   pfevents->numKeys = 0;
}

/******************************************************************************
*            Panel Creation and Management
******************************************************************************
*/

static pfuGUIString viewModel_strs[] = {"Trackball", "Fly", "Drive"};
static int viewModel_vals[] = {
    PFITDF_TRACKBALL, PFITDF_FLY, PFITDF_DRIVE};


static pfuPanel *
InitPanel(void)
{
    float  xOrigin, yOrigin, ySize, xSize;
    int x, y, yTop;
    pfuWidget *wid;
    pfuPanel *pan;

    pan = pfuNewPanel();

    pfuGetPanelOriginSize(pan, &xOrigin, &yOrigin, &xSize, &ySize);

    x = (int)xOrigin;
    yTop = (int)(yOrigin + ySize);
    y = (int)yTop - PFUGUI_BUTTON_YINC;

    // ---- ROW 1 ---- ///
   // action  buton - disable the gui (F1KEY to get it back)
    wid = pfuNewWidget(pan, PFUGUI_SWITCH, 0);
    pfuWidgetDim(wid,  x,  y,  24,  24);
    pfuWidgetValue(wid, 1.0f);
    pfuWidgetDefaultValue(wid, 1.0f);
    pfuWidgetActionFunc(wid, KillGUI);
    Shared->wKillGUI = wid;
    x += 24 + PFUGUI_PANEL_FRAME;

    // action  buton - reset to origin button
    wid = pfuNewWidget(pan, PFUGUI_BUTTON, CTL_REPOSITION);
    pfuWidgetDim(wid,  x,  y,  PFUGUI_BUTTON_VLONG_XSIZE,
       PFUGUI_BUTTON_YSIZE);
    pfuWidgetLabel(wid, "Reposition");
    pfuWidgetActionFunc(wid, PanelControl);
    x += PFUGUI_BUTTON_VLONG_XINC;

    // the message bar with positions
    wid = pfuNewWidget(pan, PFUGUI_MESSAGE, 0);
    pfuWidgetDim(wid,  x,  y,  PFUGUI_MESSAGE_XSIZE,
       PFUGUI_MESSAGE_YSIZE);
    pfuWidgetActionFunc(wid, PanelControl);
    x += PFUGUI_MESSAGE_XINC;
    Shared->wPosXYZ = wid;


    // action button - reset all
    wid = pfuNewWidget(pan, PFUGUI_BUTTON, CTL_RESET_ALL);
    pfuWidgetDim(wid,  x,  y,  PFUGUI_BUTTON_VLONG_XSIZE,
       PFUGUI_BUTTON_YSIZE);
    pfuWidgetLabel(wid, "Reset All");
    pfuWidgetActionFunc(wid, PanelControl);
    Shared->wResetAll = wid;

    x = (int)xOrigin;
    y = (int)yTop - 2*PFUGUI_BUTTON_YINC;

   // -------------------- //
   // ------- ROW 2 ------ //
   // -------------------- //
    // action button - quit
    wid = pfuNewWidget(pan, PFUGUI_BUTTON, CTL_QUIT);
    pfuWidgetDim(wid,  x,  y,  PFUGUI_BUTTON_XSIZE,  PFUGUI_BUTTON_YSIZE);
    pfuWidgetActionFunc(wid, PanelControl);
    pfuWidgetLabel(wid, "Quit");
    x += PFUGUI_BUTTON_XINC;

    // menu button - view model
    wid = pfuNewWidget(pan, PFUGUI_MENU_BUTTON, CTL_MODEL);
    pfuWidgetDim(wid,  x,  y,  PFUGUI_BUTTON_VLONG_XSIZE,
       PFUGUI_BUTTON_YSIZE);
    pfuWidgetLabel(wid, "Motion");
    pfuWidgetActionFunc(wid, PanelControl);
    pfuWidgetSelections(wid, viewModel_strs, viewModel_vals, NULL, 3);
    Shared->wFModel = wid;
    x += PFUGUI_BUTTON_VLONG_XINC;

    // switch button - stats
    wid = pfuNewWidget(pan, PFUGUI_SWITCH, CTL_DIAGS);
    pfuWidgetDim(wid, x, y, PFUGUI_BUTTON_MED_XSIZE, PFUGUI_BUTTON_YSIZE);
    pfuWidgetLabel(wid, "Stats");
    pfuWidgetActionFunc(wid, PanelControl);
    Shared->wStats = wid;
    x += PFUGUI_BUTTON_MED_XINC;

    // switch button - tree
    wid = pfuNewWidget(pan, PFUGUI_SWITCH, CTL_TREE);
    pfuWidgetDim(wid, x, y, PFUGUI_SCALE_XSIZE(80), PFUGUI_BUTTON_YSIZE);
    pfuWidgetLabel(wid, "Tree");
    pfuWidgetActionFunc(wid, PanelControl);
    Shared->wTree = wid;
    x += PFUGUI_BUTTON_MED_XINC;

    // switch button - wireframe
    wid = pfuNewWidget(pan, PFUGUI_SWITCH, CTL_WIREFRAME);
    pfuWidgetDim(wid, x, y, PFUGUI_SCALE_XSIZE(80), PFUGUI_BUTTON_YSIZE);
    pfuWidgetLabel(wid, "Wire");
    pfuWidgetActionFunc(wid, PanelControl);
    Shared->wWireframe = wid;
    x += PFUGUI_BUTTON_MED_XINC;

    // switch button - normals
    wid = pfuNewWidget(pan, PFUGUI_SWITCH, CTL_NORMALS);
    pfuWidgetDim(wid, x, y, PFUGUI_BUTTON_MED_XSIZE, PFUGUI_BUTTON_YSIZE);
    pfuWidgetLabel(wid, "Normals");
    pfuWidgetActionFunc(wid, PanelControl);
    Shared->wNormals = wid;
    x += PFUGUI_BUTTON_MED_XINC;


    x = (int)xOrigin;
    y -= PFUGUI_SLIDER_YINC;

   // -------------------- //
   // ------- ROW 3 ------ //
   // -------------------- //


      // ----- Cubelet size ------- //
    wid = pfuNewWidget(pan, PFUGUI_SLIDER, CTL_CUBLET_SIZE);
    pfuWidgetDim(wid,  x,  y,  PFUGUI_SLIDER_SMALL_XSIZE, PFUGUI_SLIDER_YSIZE);
    pfuWidgetLabel(wid, "Cublet Size");
    pfuWidgetActionFunc(wid, PanelControl);
    pfuWidgetRange(wid, PFUGUI_SLIDER, 0.05, 1.5, 0.6);
    Shared->wCubletSize = wid;
    x += PFUGUI_SLIDER_SMALL_XINC;


    // ----- Surf Threshold size ------- //
    wid = pfuNewWidget(pan, PFUGUI_SLIDER, CTL_SURF_THRESHOLD);
    pfuWidgetDim(wid,  x,  y,  PFUGUI_SLIDER_SMALL_XSIZE, PFUGUI_SLIDER_YSIZE);
    pfuWidgetLabel(wid, "Surf Thresh");
    pfuWidgetActionFunc(wid, PanelControl);
    pfuWidgetRange(wid, PFUGUI_SLIDER, 0.05, 6.0, 3.0);
    Shared->wSurfThreshold = wid;
    x += PFUGUI_SLIDER_SMALL_XINC;


    x = (int)xOrigin;
    y -= PFUGUI_SLIDER_YINC;

   // -------------------- //
   // ------- ROW 4 ------ //
   // -------------------- //

   // -------------------- //
   // ------- ROW 5 ------ //
   // -------------------- //
       return pan;
}


static void
KillGUI(pfuWidget *w)
{
   if (pfuGetWidgetValue(w) == 0.0f)
   {
      Shared->gui = 0;
      Shared->updateChannels = 1;
   }
}

//
// PanelControl
// -------------
// This function is called from the draw process from the currently
// active widget.
//

static void
PanelControl(pfuWidget *w)
{
   float val;
   switch (pfuGetWidgetId(w))
   {
   case CTL_RESET_ALL:
      pfuResetGUI();
      resetPosition();
      //Detail_mod = TRUE;
      break;
   case CTL_REPOSITION:
      resetPosition();
      //Detail_mod = TRUE;
      break;
   case CTL_QUIT:
      Shared->exitFlag = 1;

      pfNotify(PFNFY_DEBUG, PFNFY_PRINT,
               " Have Quit button - bye...\n");

      break;
   case CTL_MODEL:
      val = pfuGetWidgetValue(w);
      Shared->xformerModel = (int)val;
      xformerModel((int)val, Shared->collideMode);

      pfNotify(PFNFY_DEBUG, PFNFY_PRINT,
               " Have Viewing Model: %.0f\n", val);

      break;
   case CTL_DIAGS:
      if (pfuGetWidgetValue(w) == 0.0f)
         Shared->drawStats = 0;
      else
         Shared->drawStats = 1;
      break;
//    case CTL_TREE:
   case CTL_WIREFRAME:
      if (pfuGetWidgetValue(w) == 0.0f)
         Shared->globalSceneState->setMode(PFSTATE_ENWIREFRAME, PFTR_OFF);
      else
         Shared->globalSceneState->setMode(PFSTATE_ENWIREFRAME, PFTR_ON);
      break;

   case CTL_NORMALS:
      if(pfuGetWidgetValue(w) == 0.0f)
      {
//         theApp->drawNormals = false;
         std::cout << "Setting normals: off\n" << endl;
      }
      else
      {
//         theApp->drawNormals = true;
         std::cout << "Setting normals: on\n" << endl;
      }
      break;

   case CTL_OUTPUT_SCENE:
      /* pfdStoreFile(Shared->sceneParent, "myviewer_output.pfb"); */
      pfdStoreFile(Shared->scene, "myviewer_output.pfb");
      break;


   case CTL_CUBLET_SIZE:
//      theApp->cubeletSize = pfuGetWidgetValue(Shared->wCubletSize);
//      std::cout << "New cubletSize: " << theApp->cubeletSize << endl;
      break;

   case CTL_SURF_THRESHOLD:
//      theApp->surfaceThreshold = pfuGetWidgetValue(Shared->wSurfThreshold);
//      std::cout << "New surfThreshold: " << theApp->surfaceThreshold << endl;
      break;


   default:

      pfNotify(PFNFY_DEBUG, PFNFY_PRINT,
               "Have GUI Widget \"%s\": id=%d, val = %f\n",
               pfuGetWidgetLabel(w), pfuGetWidgetId(w), pfuGetWidgetValue(w));
      break;
   }

}

static void
updateGUIViewMsg(pfCoord *viewpt)
{
    static char     posBuf[256];

    sprintf(posBuf," X%5.1f Y%5.1f Z%5.1f H%5.1f P%5.1f R%5.1f",
       viewpt->xyz[PF_X],viewpt->xyz[PF_Y],viewpt->xyz[PF_Z],
       viewpt->hpr[PF_H],viewpt->hpr[PF_P],viewpt->hpr[PF_R]);
    pfuWidgetLabel(Shared->wPosXYZ, posBuf);
}

/******************************************************************************
*            Draw Process: Graphics Initialization
******************************************************************************/

//
// OpenPipeWin() -- create a pipeline: this procedure is executed in
// the draw process (when there is a separate draw process).
static void
OpenPipeWin(pfPipeWindow *pw)
{
    static pfVec4  bg_color(0.0f, 0.0f, 0.0f, 0.0f);
    pw->open();
    pfClear(PFCL_COLOR, &bg_color);
    pw->swapBuffers();
}

/******************************************************************************
*            Draw Process Routines
******************************************************************************
*/

//
// DrawChannel() -- draw a channel and read input queue. this
// procedure is executed in the draw process (when there is a
// separate draw process).
//
static void
DrawChannel (pfChannel *channel, void *)
{
   static pfVec4 bgclr(0.0f, 0.0f, 0.0f, 1.0f);

   // erase framebuffer and draw Earth-Sky model
   pfClear(PFCL_COLOR | PFCL_DEPTH, &bgclr);

   // invoke Performer draw-processing for this frame
   pfDraw();

   // Check for OpenGL errors
   GLenum err = glGetError();
   if (err != GL_NO_ERROR)
      pfNotify(PFNFY_NOTICE,PFNFY_USAGE,
               "OpenGL Error 0x%x - %s",(unsigned)err, gluErrorString(err));


   // Enable drawing of Performer throughput statistics
   if (Shared->drawStats)
      channel->drawStats();

   // Check the mouse and keyboard = only needed for GL input
   // This is done after the draw becuase it can happen in parallel
   // with the pipe finishing the rendering of the frame.
   //
   pfuCollectInput();
}

/******************************************************************************
*            Cull Process Routines
******************************************************************************
*/

//
// CullChannel() -- traverse the scene graph and generate a
//    display list for the draw process.  This procedure is
// executed in the cull process.
//
static void
CullChannel(pfChannel *, void *)
{
    // pfDrawGeoSet or other display listable Performer routines
    // could be invoked before or after pfCull()
    pfCull();
}


static int PickHitCB(pfiPick* pick, void* data)
{
   int count = pick->getCount();
   if (count > 0)
   {
      pfNode* n = pick->getNode();
      if (n != NULL)
         pfNotify(PFNFY_NOTICE,PFNFY_PRINT,
                  "PickHitCB -- %d hits: first node %s of type %s",
                  count, n->getName(), n->getClassType()->getName());
      else
         pfNotify(PFNFY_NOTICE,PFNFY_PRINT, "PICK %d hits: NULL pick node", count);
   }
   return PFTRAV_TERM;
}




