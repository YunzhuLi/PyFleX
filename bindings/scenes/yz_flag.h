
class yz_FlagCloth: public Scene
{
public:

	yz_FlagCloth(const char* name) : Scene(name) {}

	void Initialize(py::array_t<float> scene_params, int thread_idx = 0)
	{
        auto ptr = (float *) scene_params.request().ptr;

                float height = ptr[0];
        int dimx = ptr[1];
		int dimy = ptr[2];
        float stretchStiffness = ptr[3];
		float bendStiffness = ptr[4];
		float shearStiffness = ptr[5];
		float windStrength = ptr[6];

		float draw_mesh = ptr[7];

		float radius = 0.05f;

		int phase = NvFlexMakePhase(0, eNvFlexPhaseSelfCollide);

        // void CreateSpringGrid(Vec3 lower, int dx, int dy, int dz, float radius, int phase, float stretchStiffness, float bendStiffness, float shearStiffness, Vec3 velocity, float invMass)
        CreateSpringGrid(Vec3(0.0f, 0.0f, -height), dimx, dimy, 1, radius, phase, stretchStiffness, bendStiffness, shearStiffness, 0.0f, 1.0f);

		const int c1 = 0;
		const int c2 = dimx - 1;
		control_idx_0 = c1;
		control_idx_1 = c2;

		g_buffers->positions[c1].w = 0.0f;
		g_buffers->positions[c2].w = 0.0f;

		// add tethers
		for (int i=0; i < int(g_buffers->positions.size()); ++i)
		{
			// hack to rotate cloth
			swap(g_buffers->positions[i].y, g_buffers->positions[i].z);
			g_buffers->positions[i].y *= -1.0f;

			g_buffers->velocities[i] = RandomUnitVector()*0.1f;

			float minSqrDist = FLT_MAX;

			if (i != c1 && i != c2)
			{
				float stiffness = -0.8f;
				float give = 0.1f;

				float sqrDist = LengthSq(Vec3(g_buffers->positions[c1])-Vec3(g_buffers->positions[c2]));

				if (sqrDist < minSqrDist)
				{
					CreateSpring(c1, i, stiffness, give);
					CreateSpring(c2, i, stiffness, give);

					minSqrDist = sqrDist;
				}
			}
		}

		g_params.radius = radius*1.0f;
		g_params.dynamicFriction = 0.25f;
		g_params.dissipation = 0.0f;
		g_params.numIterations = 4;
		g_params.drag = 0.06f;
		g_params.relaxationFactor = 1.0f;

		g_numSubsteps = 2;

		// draw options
		if (!draw_mesh) {
			g_drawPoints = true;
			g_drawSprings = true;
			g_drawMesh = false;
		}
		else {
			g_drawPoints = false;
			g_drawSprings = false;
		}

		g_windFrequency *= 2.0f;
		g_windStrength = windStrength;
	}

	int control_idx_0, control_idx_1;

	void Update(py::array_t<float> update_params)
	{
	    // update wind
		const Vec3 kWindDir = Vec3(0.0f, 0.0f, -1.0f);
		Vec3 wind = g_windStrength*kWindDir;
				
		g_params.wind[0] = wind.x;
		g_params.wind[1] = wind.y;
		g_params.wind[2] = wind.z;

        // update action
        auto ptr = (float *) update_params.request().ptr;

        float dx_0 = ptr[0];
	    float dy_0 = ptr[1];
	    float dz_0 = ptr[2];

	    g_buffers->positions[control_idx_0].x += dx_0;
	    g_buffers->positions[control_idx_0].y += dy_0;
	    g_buffers->positions[control_idx_0].z += dz_0;

	    g_buffers->velocities[control_idx_0].x = dx_0 / g_dt;
        g_buffers->velocities[control_idx_0].y = dy_0 / g_dt;
        g_buffers->velocities[control_idx_0].z = dz_0 / g_dt;

        float dx_1 = ptr[3];
	    float dy_1 = ptr[4];
	    float dz_1 = ptr[5];

	    g_buffers->positions[control_idx_1].x += dx_1;
	    g_buffers->positions[control_idx_1].y += dy_1;
	    g_buffers->positions[control_idx_1].z += dz_1;

	    g_buffers->velocities[control_idx_1].x = dx_1 / g_dt;
        g_buffers->velocities[control_idx_1].y = dy_1 / g_dt;
        g_buffers->velocities[control_idx_1].z = dz_1 / g_dt;
	}
};

