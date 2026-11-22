~~~mermaid
sequenceDiagram
  autonumber
  participant M as main()
  participant K as GetKeyPress
  participant S as SDL2
  participant C as Camera
  participant T as CreateGeodesicThreads
  participant W as Worker thread ×N
  participant G as GeodesicRayIntegrator
  loop every frame while running
    M->>M: deltaTime = now − lastTime
    M->>K: GetKeyPress(event, running, cam)
    loop while SDL_PollEvent returns an event
      K->>S: SDL_PollEvent(&event)
      alt arrow key
        K->>C: SetPosition(position ± 0.025)
      else Q
        K->>C: SetLookAt(origin)
      else Esc or window closed
        K-->>M: running = false
      end
    end
    M->>T: CreateGeodesicThreads(pixelBuffer, N, cam, …)
    loop i = 0 … N−1
      T->>W: spawn thread for rows startY … endY
    end
    par each worker in parallel
      loop every pixel in its band
        W->>G: GeodesicRayTrace(band)
        G->>C: GenerateRay(U, V, ray)
        G->>G: RK4Step until horizon, disk or escape
        G->>G: SetPixel(buffer, x, y, color)
      end
    end
    T->>W: join() all threads
    T-->>M: frame complete
    M->>M: move light, THETA += 0.5
    M->>S: SDL_UpdateTexture(pixelBuffer)
    M->>S: RenderClear → RenderCopy → RenderPresent
  end
  M->>S: Destroy texture, renderer and window, then SDL_Quit()
~~~
