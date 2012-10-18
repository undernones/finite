#include "Options.h"
#include <gflags/gflags.h>

namespace
{

DEFINE_string(framesDir, "frames", "Directory where frames and other data get dumped");
DEFINE_string(restoreFile, "???", "Checkpoint file for restoring a simulation");
DEFINE_string(meshFile, "meshes/bunny.mesh", "Mesh file");
DEFINE_double(dt, 1.0 / 120, "Timestep");
DEFINE_double(fps, 30, "Number of frames to generate per second");
DEFINE_double(duration, 10, "Length of simulation in playback time");
DEFINE_int32(framesPerChkpt, 10, "How often to generate checkpoint files");
DEFINE_bool(disableChkpts, false, "Whether to disable the saving of checkpoints");
DEFINE_double(density, 1000, "Material density. Defaults to that of water.");
DEFINE_double(lambda, 8000, "Lame constant preserving volume");
DEFINE_double(mu, 8000, "Lame constant of stiffness");
DEFINE_double(friction, 0.05, "Tangential friction with obstacles");
DEFINE_double(flowRate, 0, "Rate of plastic flow");
DEFINE_double(yieldPoint, 2000, "Stress level at which plastic flow begins");
DEFINE_double(K, 0, "Work hardening (+ values) or softening (- values)");
DEFINE_double(gravity, -9.81, "Acceleration due to gravity in the -y direction");

}

std::string Options::framesDir() { return FLAGS_framesDir; }
std::string Options::restoreFile() { return FLAGS_restoreFile; }
std::string Options::meshFile() { return FLAGS_meshFile; }
double Options::dt() { return FLAGS_dt; }
double Options::fps() { return FLAGS_fps; }
double Options::duration() { return FLAGS_duration; }
uint32_t Options::framesPerChkpt() { return FLAGS_framesPerChkpt; }
bool Options::disableChkpts() { return FLAGS_disableChkpts; }
double Options::density() { return FLAGS_density; }
double Options::lambda() { return FLAGS_lambda; }
double Options::mu() { return FLAGS_mu; }
double Options::friction() { return FLAGS_friction; }
double Options::flowRate() { return FLAGS_flowRate; }
double Options::yieldPoint() { return FLAGS_yieldPoint; }
double Options::K() { return FLAGS_K; }
double Options::gravity() { return FLAGS_gravity; }

bool
Options::init(int *argc, char ***argv)
{
    //google::SetUsageMessage("use it wisely");
    //google::SetVersionString("0.00");
    return google::ParseCommandLineFlags(argc, argv, true);
}
