/*
 * Project Vending_Machine
 * Description: Vending Machine Backend
 * Author: Stephen Wallace
 * Date: 24/02/2021
 */
#include <string.h>

float credit = 0.00;
static int numItems = 9;
static float itemPrices[] {1.99, 2.99, 1, 2, 1.49, 0.89, 1.59, 0.75, 0.5, 0.45};

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  Particle.function("returnMoney", moneyOutput);
  Particle.function("addMoney", addMoney);
  Particle.function("buy", selectItem);
  Particle.variable("credit", credit);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}

int moneyOutput(String command){
  Particle.publish("Returning Money", String(credit), PRIVATE);
  credit = 0.00;

  return 0;
}

int addMoney(String value){
  float temp = value.toFloat();
  if (temp >= 0){
    credit = credit + temp;
  }

  return 0;
}

int selectItem(String itemNum){
  int itemSelected = itemNum.toInt();
  if (itemSelected >= 1 && itemSelected <= 9){
    if (credit >= itemPrices[itemSelected-1]){
      Particle.publish("Bought item #", String(itemSelected), PRIVATE);
      credit = credit - itemPrices[itemSelected-1];
      return 0;
    }
    Particle.publish("Not Enough Money", PRIVATE);
    return 0;
  }
  Particle.publish("Invalid Selection", String(itemSelected), PRIVATE);
  return 0;
}