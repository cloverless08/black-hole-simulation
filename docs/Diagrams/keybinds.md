~~~mermaid
flowchart TD
  A(["GetKeyPress(event, running, cam)"]) --> B{"SDL_PollEvent(&event)<br>returned an event?"}
  B -->|no| Z(["Return to main loop"])
  B -->|yes| C{"event.type"}
  C -->|SDL_QUIT| QUIT["running = false"]
  QUIT --> B
  C -->|SDL_KEYDOWN| D{"key"}
  D -->|Esc| QUIT
  D -->|"→"| R1["cam.SetPosition(pos + (0.025, 0, 0))"]
  D -->|"←"| R2["cam.SetPosition(pos + (−0.025, 0, 0))"]
  D -->|"↑"| R3["cam.SetPosition(pos + (0, 0, −0.025))"]
  D -->|"↓"| R4["cam.SetPosition(pos + (0, 0, 0.025))"]
  D -->|Q| R5["cam.SetLookAt(origin)"]
  D -->|"D · S · P"| R6["log only: diagnostics,<br>screenshot, pause not built yet"]
  D -->|other| B
  R1 --> B
  R2 --> B
  R3 --> B
  R4 --> B
  R5 --> B
  R6 --> B
  C -->|SDL_KEYUP| U["log release of Esc or arrows"]
  U --> B
  C -->|other| B
~~~
