~~~mermaid
flowchart LR
  subgraph SRC["src/"]
    main["main.cpp<br>main()"]
    keyb["keybinds.cpp<br>GetKeyPress()"]
    thr["threading.cpp<br>Create…Threads()"]
    loopc["loop.cpp<br>test_loop() — unused"]
    post["postprocessing.cpp<br>PostProcess — stub"]
  end
  subgraph INC["include/"]
    utils["main_utils.h<br>StrOut, SetPixel, Length3D, RandInt"]
    vec["vec.h<br>math::Vec3, math::Vec2"]
  end
  subgraph RT["raytrace/"]
    cam["camera.h/.cpp<br>Camera"]
    ray["ray.h/.cpp<br>Ray"]
    integ["rayintegrator.h + 3 .cpp<br>Linear · Marching · Geodesic"]
    subgraph OBJ["objects/"]
      ob["ObjectBase → ObjSphere"]
      lb["LightBase → PointLight"]
    end
  end
  subgraph AST["astronomy/ (not compiled)"]
    bh["BlackHole"]
  end
  qb[("qbLinearAlgebra<br>qbVector, qbMatrix")]
  sdl[("SDL2<br>window · events · texture")]
  main -->|"polls input"| keyb
  main -->|"renders frame"| thr
  main -->|"builds scene"| ob
  main -->|"builds scene"| lb
  main -->|"configures"| cam
  main -->|"window, present"| sdl
  main -->|"logging"| utils
  keyb -->|"SDL_PollEvent"| sdl
  keyb -->|"moves"| cam
  thr -->|"one thread per band"| integ
  integ -->|"GenerateRay"| cam
  integ -->|"TestIntersection"| ob
  integ -->|"ComputeIllumination"| lb
  integ -->|"SetPixel"| utils
  integ -->|"RK4 math"| vec
  loopc -->|"SetPixel"| utils
  cam --> ray
  cam --> qb
  ray --> qb
  ob --> qb
  lb --> qb
  utils --> qb
  bh -.->|"inherits"| ob
~~~
