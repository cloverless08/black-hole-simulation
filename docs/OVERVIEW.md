Milestones:
 - Blank Window
 - Statis 2D version (output to file ig)
 - Raymarching + SDL2 Integration
 - Add gravitational lensing
 - Add horizon absorption
 - Add accretion disk
 - Camera controls
 - Change from newtonion to geodesic integration
 - Add multithreading


Option A — Newtonian ray bending (easier, good enough to look convincing)
Treat light as a particle affected by Newtonian gravity from the black hole's mass. Integrate F = GMm/r² on the ray's direction each step. Not physically accurate but visually gives you lensing, and it's cheap to implement and reason about.
Option B — Schwarzschild geodesics (harder, physically correct)
Integrate the actual geodesic equations of the Schwarzschild metric (or just use the known impact-parameter/photon-orbit equations). This gives you the real photon sphere, real light bending, accurate accretion disk warping. More math, but not enormous — there are well-documented closed forms and RK4 integration schemes for this that many hobbyist raytracers use.

Utilize geometric ratio units, like 1M and 2M or 19M, instead of fixed or approximate units (SI Units).
r_s = 2M = 2 event horizon (Schwarzschild radius) r_ph = 3M = 3 photon sphere ISCO = 6M = 6 innermost stable circular orbit
Physical constants were absorbed into the unit system so that all simulation lengths are expressed as multiples of the gravitational radius GM/c², which keeps every quantity in the integrator within a few orders of magnitude of unity and avoids catastrophic loss of floating-point precision.

Backwards ray-trace from camera into space, four possible endings for every ray:
- Falls into event horizon → black (“shadow”)
- Crosses disk plane, between r_in and r_out → disk colour
- Escapes to large radius → lands in star field
- runs out of integration stpes → black (wouldve been captured anyway)

	

