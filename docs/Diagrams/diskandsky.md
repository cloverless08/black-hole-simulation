~~~mermaid
flowchart LR
  subgraph AD["AccretionDisk(r)"]
    direction TB
    d1(["r between 6M and 20M"]) --> d2["t = (r − 6M) / (20M − 6M)"]
    d2 --> d3["color = inner (255, 230, 180) · (1 − t)<br>+ outer (140, 30, 5) · t"]
    d3 --> d4["brightness = clamp((6M / r)^1.5, 0, 1)"]
    d4 --> d5(["return color · brightness"])
  end
  subgraph BG["RenderBackground(dir)"]
    direction TB
    b1(["unit direction dir"]) --> b2["θ = acos(clamp(dir.z))<br>φ = atan2(dir.y, dir.x) + π"]
    b2 --> b3["row = int(θ / π · 36)<br>col = int(φ / 2π · 72)"]
    b3 --> b4{"(row + col) even?"}
    b4 -->|yes| b5["color = (40, 40, 60)"]
    b4 -->|no| b6["color = (15, 15, 25)"]
    b5 --> b7["hash = mix(int(θ · 300), int(φ · 300))"]
    b6 --> b7
    b7 --> b8{"hash mod 1000 #lt; 3?"}
    b8 -->|yes| b9["color = (255, 255, 255) star"]
    b8 -->|no| b10(["return color"])
    b9 --> b10
  end
  AD ~~~ BG
~~~
