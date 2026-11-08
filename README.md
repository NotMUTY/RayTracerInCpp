# RayTracerInCpp
Some Spheres And Lights Make them Shinieee!!

reqs : computer that works and uses windows, g++

there is two rendering modes;
  -DSINGLE flag -> Only 1 cpu thread and works slow :((
  -DMULTI flag -> creates as much thread is set in settings.h AND WORKS FAST :)))

what this program does:
  this program somehow calculates and traces rays and compares to the sun rays and decides how bright pixel should be

how it does this:
  camera and viewplane coordinates creates a ray that goes to infinity and if it hits something it calculates how much look alike to the suns ray

how to use
  run build.bat for only compilation
    it deletes old exe and tries to build one again
  run run.bat for execute builded exe
    only runs so it only runs the runnable executable
  run brun.bat for building and running
    you got the point yea

how program starts:
  configures window -> creates window -> calls RInitRenderer -> calls InitWorld -> InitWorld calls InitCamera -> InitWorld calss InitSun -> InitWorld calls Start -> program enters loop

how loop works:
  calls Update -> calls RRenderScreen

what function does what?:
  RInitRenderer:
    creates bitmap info

  InitWorld:
    Creates Camera
    Creates Sun
    Sets cursor position to its place

  InitCamera:
    Creates Camera with position, rotation, fov
    Calculates pixel steps for scaling viewplane to resolution

  InitSun:
    Creates the sun

  Start:
    This is the place where you can do anything and not break something at the same time.

  Update:
    This is the place where you can do anything and not break something at the same time BUT WORKS EVER FRAME.

  RRenderScreen:
    if single threaded calculates all the objects creates in the world to the sun and renders how bright every pixel should be
    if multi threaded same thing but better and faster

i wanna configure something and not break anything at the same time:
  setting.h got your back

i wanna create objects??:
  Object::CreateObj<TYPENAME>(position, rotation, scale, isactive, OBJEXTRAARGS...) and it creates 

  !!! ONLY 128 OBJECTS ARE ALLOWED AT THE SAME TIME
  !!! CAMERA AND SUN ARE IN OBJ LIST SO IT GOES DOWN TO 126

