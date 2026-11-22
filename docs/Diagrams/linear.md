~~~mermaid
flowchart TD
  A(["LinearRayTrace(rows startY … endY)"]) --> B{"next pixel in band?"}
  B -->|no| Z(["Return"])
  B -->|yes| C["U, V from pixel<br>cam.GenerateRay(U, V, camRay)"]
  C --> D{"next object in objectList?"}
  D -->|no| B
  D -->|yes| E["object → TestIntersection(camRay,<br>intPoint, localNorm, localColor)"]
  E --> F{"hit?"}
  F -->|no| G["SetPixel black"]
  G --> D
  F -->|yes| H["for each light: ComputeIllumination(…)<br>last light's result is kept"]
  H --> I["dist = |intPoint − camRay origin|<br>update min / max (debug only)"]
  I --> J{"lit?"}
  J -->|yes| K["SetPixel red = 255 · intensity"]
  K --> D
  J -->|no| G
~~~
