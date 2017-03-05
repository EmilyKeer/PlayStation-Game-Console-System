void buttonInit(){
    buttonDownState = digitalRead(PBD1);
    buttonUpState = digitalRead(PBU1);
    buttonConfirmState = digitalRead(PBC1);
    buttonCancelState = digitalRead(PBC2);
  }

void pinModInit(){
    pinMode(PBD1, INPUT_PULLDOWN);
    pinMode(PBU1, INPUT_PULLDOWN);
    pinMode(PBC1, INPUT_PULLUP);
    pinMode(PBC2, INPUT_PULLUP);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
  }

