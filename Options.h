#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

class Options
{
public:
    static std::string framesDir();
    static std::string restoreFile();
    static std::string meshFile();
    static double dt();
    static uint32_t fps();
    static double duration();
    static uint32_t framesPerChkpt();
    static bool disableChkpts();
    static double density();
    static double lambda();
    static double mu();
    static double friction();
    static double flowRate();
    static double yieldPoint();
    static double K();
    static double gravity();

    static bool init(int argc, char* argv[]);

private:
    Options();
    Options(const Options &o);
    ~Options();
	Options& operator =(const Options &);
};

#endif // OPTIONS_H
