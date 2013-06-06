//PCA on/off states
#define ON 0x42
#define OFF 0x02

//Function Prototypes
void PCA_init(void);
void PCA_setDutyCycle(unsigned char duty);
void PCA_setDirection(unsigned char dir);