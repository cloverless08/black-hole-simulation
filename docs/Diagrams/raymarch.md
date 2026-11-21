~~~mermaid
flowchart TD
  A(["MarchRayTrace(rows startY … endY)"]) --> B{"next pixel in band?"}
  B -->|no| Z(["Return"])
  B -->|yes| C["stepsIncreasing = 0, lastDist = 0<br>GenerateRay(U, V), hit = false"]
  C --> D{"next object?"}
  D -->|yes| D2{"stepsIncreasing ≥ 2?"}
  D2 -->|yes| R
  D2 -->|no| E["origin, unit dir<br>distance = 0, step = 0"]
  E --> F{"step #lt; 128?"}
  F -->|yes| G["p = origin + distance · dir<br>d = |p| − 1  (unit-sphere SDF)"]
  G --> H{"d #gt; lastDist?"}
  H -->|yes| H1["stepsIncreasing += 1"]
  H1 --> I
  H -->|no| I{"d ≤ 0.025?"}
  I -->|yes| J["hit = true, intPoint = p<br>normal = normalize(p)"]
  I -->|no| K{"distance #gt; 10?"}
  K -->|no| L["distance += d, step += 1"]
  L --> F
  K -->|yes| D
  F -->|no| D
  D -->|no| R{"hit?"}
  J --> R
  R -->|yes| S["ComputeIllumination for each light<br>SetPixel grey = 255 · intensity"]
  R -->|no| T["SetPixel black"]
  S --> B
  T --> B
~~~
