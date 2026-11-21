~~~mermaid
flowchart TD
  A(["Create…Threads(buffer, numThreads, cam, height, width, …)"]) --> B["threads = empty list<br>construct the integrator"]
  B --> C["i = 0"]
  C --> D{"i #lt; numThreads?"}
  D -->|yes| E["startY = i · height / numThreads<br>endY = (i + 1) · height / numThreads"]
  E --> F["threads.emplace_back(Integrator::Trace,<br>buffer, cam, startY, endY, …)"]
  F --> G["i += 1"]
  G --> D
  D -->|no| H{"next thread joinable?"}
  H -->|yes| I["t.join()"]
  I --> H
  H -->|"no more"| J(["Return: whole frame is in buffer"])
~~~
