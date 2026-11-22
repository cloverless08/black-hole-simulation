~~~mermaid
flowchart LR
  subgraph SPH["ObjSphere::TestIntersection(castRay)"]
    direction TB
    s1(["enter"]) --> s2["v̂ = normalize(castRay.m_lab)"]
    s2 --> s3["b = 2 · (origin · v̂)<br>c = origin · origin − 1   (a = 1)"]
    s3 --> s4{"b² − 4c #gt; 0?"}
    s4 -->|no| s9(["return false"])
    s4 -->|yes| s5["t1, t2 = (−b ± √(b² − 4c)) / 2"]
    s5 --> s6{"t1 #lt; 0 or t2 #lt; 0?<br>behind camera"}
    s6 -->|yes| s9
    s6 -->|no| s7["intPoint = origin + v̂ · min(t1, t2)<br>localNorm = normalize(intPoint)"]
    s7 --> s8(["return true"])
  end
  subgraph PL["PointLight::ComputeIllumination(intPoint, localNorm, …)"]
    direction TB
    p1(["enter"]) --> p2["L = normalize(m_location − intPoint)"]
    p2 --> p3["angle = acos(localNorm · L)"]
    p3 --> p4{"angle #gt; π/2?<br>surface faces away"}
    p4 -->|yes| p5(["color = m_color, intensity = 0<br>return false"])
    p4 -->|no| p6(["color = m_color<br>intensity = m_intensity · (1 − angle / (π/2))<br>return true"])
  end
  SPH ~~~ PL
~~~
