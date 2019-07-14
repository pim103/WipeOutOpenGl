#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

class Controller {
    public:
        Controller();
        void GetPlayerIntent(unsigned char);
        void ReleasePlayerIntent(unsigned char key);

        bool wantToMoveForward;
        bool wantToMoveBack;
        bool wantToMoveRight;
        bool wantToMoveLeft;
    private:
    protected:
};

#endif // CONTROLLER_H_INCLUDED
