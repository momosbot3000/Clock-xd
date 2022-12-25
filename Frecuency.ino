void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);

  uint8_t Notes[][2] = {
    {54, 4}, {61, 4}, {59, 4}, //0
    {61, 12}, {54, 4}, {61, 4}, {59, 4}, //1
    {61, 12}, {54, 4}, {61, 4}, {59, 4}, //2
    {56, 12}, {57, 16}, //3
    {0, 8}, {54, 4}, {61, 4}, {59, 4}, //4
    {61, 12}, {54, 4}, {61, 4}, {59, 4}, //5
    {64, 12}, {62, 12}, //6
    {61, 28}, //7
    {0, 8}, {54, 4}, {61, 4}, {59, 4}, //8
    {61, 8}, {0, 4}, {64, 8}, {0, 4}, //9
    {61, 12}, {59, 8}, {0, 4}, //10
    {56, 12}, {57, 12}, //11
    {61, 8}, {0, 4}, {54, 4}, {61, 4}, {59, 4}, //12
    {61, 12}, {54, 4}, {61, 4}, {59, 4}, //13
    {57, 12}, {53, 12}, //14
    {56, 24} //15   
  };

  byte bpm = 105;
  byte buzzer = 11;
  int SizeNotes =  (sizeof(Notes) / sizeof(*Notes));

  Play(Notes, SizeNotes, bpm, buzzer);
  
}


void loop() {
  
  
}

float Frecuency(int note, int octave){
  
  int hz = 440 * pow(1.05946309436, 12 * (octave - 4) + note - 10);
  return hz;

}


float nKey_Hz(uint8_t nKey){

  if(nKey >= 1 && nKey <= 88){
    int sum = 0;
    nKey += 9;
    while(nKey > 12){
      sum++;    
      nKey -= 12;
    }
    int N = nKey;
    int Oc = sum;
  
    float hz = Frecuency(N, Oc);
    return hz;
  }
  else {
    return 0;
  }
}


void Play(uint8_t Notes[][2], int SizeNotes, byte bpm, byte buzzer){
  
  float start = millis();
  float keep = start;
  float beatDuration = 60000 / bpm;

  for (int i = 0; i < SizeNotes; i++) {
    
    float noteDuration = (Notes[i][1] * beatDuration) / 8; 
    float Frecuency = nKey_Hz(Notes[i][0]);

    if(Frecuency > 0){    
      while(millis() <= keep + (noteDuration * 0.9)){
        tone(buzzer, Frecuency);
      }
      while(millis() >= keep + (noteDuration * 0.9) && millis() <= keep + noteDuration){    
        noTone(buzzer);
      }
    }
    else{
      while(millis() <= keep + noteDuration){
        noTone(buzzer);
      }
    }
    keep += noteDuration;
  }
}