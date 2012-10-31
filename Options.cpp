#include "Options.h"
#include <getopt.h>

namespace
{

const std::string INVALID_FILE("???");

int disable_chkpts = 0;
std::string OPT_framesDir("frames");
std::string OPT_restoreFile(INVALID_FILE);
std::string OPT_meshFile("meshes/tet.mesh");
double OPT_dt = 1.0 / 120;
uint32_t OPT_fps = 30;
double OPT_duration = 10;
uint32_t OPT_framesPerChkpt = 10;
double OPT_density = 1000;
double OPT_lambda = 8000;
double OPT_mu = 8000;
double OPT_friction = 0.05;
double OPT_flowRate = 0;
double OPT_yieldPoint = 2000;
double OPT_hardening = 0;
double OPT_gravity = -9.81;

struct option long_options[] = {
    { "frames_dir",       required_argument, NULL,            'o' }, // output
    { "restore_file",     required_argument, NULL,            'r' }, // restore
    { "mesh_file",        required_argument, NULL,            'v' }, // vertices
    { "dt",               required_argument, NULL,            't' }, // time
    { "fps",              required_argument, NULL,            'f' }, // fps
    { "duration",         required_argument, NULL,            'u' }, // dUration
    { "frames_per_chkpt", required_argument, NULL,            'c' }, // chkpts
    { "disable_chkpts",   no_argument,       &disable_chkpts,  1  },
    { "density",          required_argument, NULL,            'd' }, // density
    { "lambda",           required_argument, NULL,            'l' }, // lambda
    { "mu",               required_argument, NULL,            'm' }, // mu
    { "friction",         required_argument, NULL,            'k' }, // friKtion
    { "flow_rate",        required_argument, NULL,            'w' }, // floW rate
    { "yield_point",      required_argument, NULL,            'y' }, // yield
    { "hardening",        required_argument, NULL,            'h' }, // hardening
    { "gravity",          required_argument, NULL,            'g' }, // gravity
};

}

std::string Options::framesDir() { return OPT_framesDir; }
std::string Options::restoreFile() { return OPT_restoreFile; }
std::string Options::meshFile() { return OPT_meshFile; }
double Options::dt() { return OPT_dt; }
uint32_t Options::fps() { return OPT_fps; }
double Options::duration() { return OPT_duration; }
uint32_t Options::framesPerChkpt() { return OPT_framesPerChkpt; }
bool Options::disableChkpts() { return disable_chkpts != 0; }
double Options::density() { return OPT_density; }
double Options::lambda() { return OPT_lambda; }
double Options::mu() { return OPT_mu; }
double Options::friction() { return OPT_friction; }
double Options::flowRate() { return OPT_flowRate; }
double Options::yieldPoint() { return OPT_yieldPoint; }
double Options::K() { return OPT_hardening; }
double Options::gravity() { return OPT_gravity; }

bool
Options::init(int argc, char* argv[])
{
    int option_index = 0;
    int c = getopt_long(argc, argv, "", long_options, &option_index);
    while (c >= 0) {
        switch (c) {
        case 'o':
            OPT_framesDir = optarg;
            break;

        case 'r':
            OPT_restoreFile = optarg;
            break;

        case 'v':
            OPT_meshFile = optarg;
            break;

        case 't':
            OPT_dt = atof(optarg);
            break;

        case 'f':
            OPT_fps = atoi(optarg);
            break;

        case 'u':
            OPT_duration = atof(optarg);
            break;

        case 'c':
            OPT_framesPerChkpt = atof(optarg);
            break;

        case 'd':
            OPT_density = atof(optarg);
            break;

        case 'l':
            OPT_lambda = atof(optarg);
            break;

        case 'm':
            OPT_mu = atof(optarg);
            break;

        case 'k':
            OPT_friction = atof(optarg);
            break;

        case 'w':
            OPT_flowRate = atof(optarg);
            break;

        case 'y':
            OPT_yieldPoint = atof(optarg);
            break;

        case 'h':
            OPT_hardening = atof(optarg);
            break;

        case 'g':
            OPT_gravity = atof(optarg);
            break;
        }
        c = getopt_long(argc, argv, "", long_options, &option_index);
    }

    return true;
}
