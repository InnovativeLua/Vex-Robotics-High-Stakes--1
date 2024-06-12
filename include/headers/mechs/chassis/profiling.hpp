class motionProfile{
public:

    enum profileTypes {E_TRAPEZOIDAL, E_SPROFILE};


    profileTypes activeProfileType;
    bool profileActive = false;

    double elapsedTime;
    double finishTime;

    double accelTime; //Time it takes to reach max speed
    double maxSpeed;


    double trapezoidalProfile();
    double SProfile();

    double calculateOutput();

    void profileTask();

    void updateProfile(double i_maxSpeed, double i_accelTime, double i_finishTime);

    void disable();
};

extern motionProfile masterProfile;