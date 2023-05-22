enum ServoState {CALLIB, IDLE, IN_PROGRESS, OFFSET};
enum DetectorState {ACTIVE, INACTIVE};

struct Servo
{
enum ServoState eState;
unsigned int uiCurrentPosition;
unsigned int uiDesiredPosition;
};

void DetectorInit(void);
void ServoCallib(void);
enum DetectorState eReadDetector(void);
void ServoInit(unsigned int);
void ServoGoTo(unsigned int);
