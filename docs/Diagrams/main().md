~~~mermaid
flowchart TD
  A(["Start main()"]) --> B["TerminalInfoHeader()<br>SDL_Delay(500)"]
  B --> C{"NUMBER_CORES == 0?"}
  C -->|yes| C1["NUMBER_CORES = 1"] --> D
  C -->|no| D["Print CPU core count and system RAM"]
  D --> E["Init locals: running = true<br>xFactor = 1/320, yFactor = 1/240<br>frame = 0, THETA = 0"]
  E --> F{"SDL_Init(VIDEO) OK?"}
  F -->|no| X1(["StrOut ERROR, return 1"])
  F -->|yes| G["SDL_CreateWindow 640 × 480"]
  G --> G1{"window OK?"}
  G1 -->|no| X1
  G1 -->|yes| H["SDL_CreateRenderer<br>accelerated + vsync"]
  H --> H1{"renderer OK?"}
  H1 -->|no| X1
  H1 -->|yes| I["SDL_CreateTexture<br>RGBA8888, streaming"]
  I --> I1{"texture OK?"}
  I1 -->|no| X1
  I1 -->|yes| J["Allocate pixelBuffer<br>640 × 480 uint32"]
  J --> K["Camera: position (0, −30, 3), look at origin<br>up +z, size 0.75, aspect 4:3<br>UpdateCamera()"]
  K --> L["Scene: 2 × ObjSphere<br>1 × PointLight at (5, −10, −5)"]
  L --> M["lastTime = now()"]
  M --> N{"running?"}
  N -->|yes| O["deltaTime = now − lastTime"]
  O --> P["GetKeyPress(event, running, cam)"]
  P --> Q{"still running?"}
  Q -->|yes| R["CreateGeodesicThreads(pixelBuffer, NUMBER_CORES, …)"]
  R --> S["Move light by (r·cos θ, r·sin θ, 0)<br>THETA += 0.5"]
  S --> T["SDL_UpdateTexture from pixelBuffer"]
  T --> U["RenderClear → RenderCopy → RenderPresent"]
  U --> V["frame += 1"]
  V --> N
  Q -->|no| Z["Destroy texture, renderer, window<br>SDL_Quit()"]
  N -->|no| Z
  Z --> END(["return 0"])
~~~
