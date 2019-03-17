
class yz_MassRope : public Scene
{
public:

	yz_MassRope(const char* name) : Scene(name) {}

	void Initialize(py::array_t<float> scene_params, int thread_idx = 0)
	{
		auto ptr = (float *) scene_params.request().ptr;

		float x = ptr[0];
		float y = ptr[1];
		float z = ptr[2];
		float length = ptr[3];
		float stiffness = ptr[4];
		float draw_mesh = ptr[5];

		float radius = 0.055f;

		int group = 0;

		Vec3 velocity = RandomUnitVector()*1.0f;
		float size = radius*5.f;

		// void CreateParticleShape(const Mesh* srcMesh, Vec3 lower, Vec3 scale, float rotation, float spacing, Vec3 velocity, float invMass, bool rigid, float rigidStiffness, int phase, bool skin, float jitter=0.005f, Vec3 skinOffset=0.0f, float skinExpand=0.0f, Vec4 color=Vec4(0.0f), float springStiffness=0.0f)
		CreateParticleShape(
		        GetFilePathByPlatform("../../data/sphere.ply").c_str(),
				Vec3(x, y, z),
				size, 0.0f, radius, velocity, 0.15f, true, 1.0f, NvFlexMakePhase(group++, 0), true, 0.0f);

		const int attachIndex = g_buffers->positions.size()-1;
		g_buffers->positions[attachIndex].w = 2.0f;

		Vec3 attachPosition = Vec3(
		        g_buffers->positions[attachIndex].x,
		        g_buffers->positions[attachIndex].y + radius/1.1f,
		        g_buffers->positions[attachIndex].z);

		Rope r;

		int start = g_buffers->positions.size();

		r.mIndices.push_back(attachIndex);

		// void CreateRope(Rope& rope, Vec3 start, Vec3 dir, float stiffness, int segments, float length, int phase, float spiralAngle=0.0f, float invmass=1.0f, float give=0.075f)
		CreateRope(r, attachPosition, Vec3(0.0f, 1.0f, 0.0f), stiffness, int(length/radius*1.1f), length, NvFlexMakePhase(group++, 0), 0.0f, 0.5f, 0.0f);

		g_ropes.push_back(r);

		// void CreateSpring(int i, int j, float stiffness, float give=0.0f)
		CreateSpring(attachIndex, start, 1.0f);

		control_idx = g_buffers->positions.size() - 1;
		g_buffers->positions[control_idx].w = 0.0f;

		g_params.radius = 0.1f;
		g_params.fluidRestDistance = radius;
		g_params.numIterations = 4;
		g_params.viscosity = 1.0f;
		g_params.dynamicFriction = 0.05f;
		g_params.staticFriction = 0.0f;
		g_params.particleCollisionMargin = 0.0f;
		g_params.collisionDistance = g_params.fluidRestDistance*0.5f;
		g_params.vorticityConfinement = 120.0f;
		g_params.cohesion = 0.0025f;
		g_params.drag = 0.06f;
		g_params.lift = 0.f;
		g_params.solidPressure = 0.0f;
		g_params.smoothing = 1.0f;
		g_params.relaxationFactor = 1.0f;
		
		g_windStrength = 0.0f;
		g_windFrequency = 0.0f;

		g_numSubsteps = 2;

		// draw options
		if (!draw_mesh) {
            g_drawPoints = true;
            g_drawMesh = false;
            g_drawRopes = false;
            g_drawSprings = true;
        }
        else {
		    g_drawPoints = false;
		    g_drawMesh = true;
		    g_drawRopes = true;
		    g_drawSprings = false;
		}

		g_ropeScale = 0.4f;
		g_warmup = false;
	}

	void Update(py::array_t<float> update_params)
	{
	    auto ptr = (float *) update_params.request().ptr;

	    float dx = ptr[0];
	    float dy = ptr[1];
	    float dz = ptr[2];

	    g_buffers->positions[control_idx].x += dx;
	    g_buffers->positions[control_idx].y += dy;
	    g_buffers->positions[control_idx].z += dz;

	    g_buffers->velocities[control_idx].x = dx / g_dt;
        g_buffers->velocities[control_idx].y = dy / g_dt;
        g_buffers->velocities[control_idx].z = dz / g_dt;
	}

	int control_idx;
};
