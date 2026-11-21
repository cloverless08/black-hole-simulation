~~~mermaid
flowchart LR
  subgraph STEP["RK4Step(pos, vel, h², dt)"]
    direction TB
    A(["enter"]) --> B["k1p = vel<br>k1v = Accel(pos)"]
    B --> C["k2p = vel + ½dt · k1v<br>k2v = Accel(pos + ½dt · k1p)"]
    C --> D["k3p = vel + ½dt · k2v<br>k3v = Accel(pos + ½dt · k2p)"]
    D --> E["k4p = vel + dt · k3v<br>k4v = Accel(pos + dt · k3p)"]
    E --> F["pos += dt/6 · (k1p + 2k2p + 2k3p + k4p)<br>vel += dt/6 · (k1v + 2k2v + 2k3v + k4v)"]
    F --> G(["return: pos, vel updated in place"])
  end
  subgraph ACC["Accel(pos, h²)"]
    direction TB
    a1["r² = pos · pos"] --> a2["r⁵ = r² · r² · √r²"]
    a2 --> a3(["return pos · (−3M · h² / r⁵)"])
  end
  STEP -.->|"called 4× per step"| ACC
~~~
