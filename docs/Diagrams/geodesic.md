~~~mermaid
flowchart TD
  A(["GeodesicRayTrace(rows startY … endY)"]) --> B{"next pixel (x, y) in band?"}
  B -->|no| Z(["Return"])
  B -->|yes| C["U = x · factorX − 1<br>V = y · factorY − 1"]
  C --> D["cam.GenerateRay(U, V, camRay)"]
  D --> E["pos = ray origin<br>vel = normalize(ray direction)"]
  E --> F["h = pos × vel, h² = h · h<br>conserved for the whole ray"]
  F --> G["color = black, step = 0"]
  G --> H{"step #lt; 2000?"}
  H -->|yes| I["r = |pos|<br>dt = clamp(0.02 r² / (r + 10), 0.005, 1)"]
  I --> J["oldPos = pos<br>RK4Step(pos, vel, h², dt)"]
  J --> K{"|pos| #lt; 2M?<br>inside event horizon"}
  K -->|no| L{"crossed z = 0<br>this step?"}
  L -->|yes| M["interpolate hit point<br>rc = |hit|"]
  M --> N{"6M #lt; rc #lt; 20M?"}
  N -->|yes| N1["color = AccretionDisk(rc)"]
  N -->|no| O{"|pos| #gt; 100M and<br>moving outward?"}
  L -->|no| O
  O -->|yes| O1["color = RenderBackground(normalize(vel))"]
  O -->|no| Q["step += 1"]
  Q --> H
  K -->|"yes: shadow"| P["SetPixel(x, y, color)"]
  H -->|"no: out of steps"| P
  N1 --> P
  O1 --> P
  P --> B
~~~
