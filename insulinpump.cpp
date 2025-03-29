#include "insulinpump.h"

InsulinPump::InsulinPump(int battery, double insulinLevel, double insulinOnBoard) :
    battery(battery),
    insulinLevel(insulinLevel),
    insulinOnBoard(insulinOnBoard)
{

}
void InsulinPump::giveBolus(int a, double b){

}
void InsulinPump::startBasalDelievery(){

}
void InsulinPump::stopBasalDelievery(){

}
void InsulinPump::raiseError(){

}
int InsulinPump::getBattery(){
    return battery;
}
void InsulinPump::setBattery(int newBattery){
    battery = newBattery;
}
double InsulinPump::getInsulinLevel(){
    return insulinLevel;
}
void InsulinPump::setgetInsulinLevel(double newLevel){
    insulinLevel = newLevel;
}
double InsulinPump::getInsulinOB(){
    return insulinOnBoard;
}
void InsulinPump::setInsulinOB(double newOB){
    insulinOnBoard = newOB;
}
