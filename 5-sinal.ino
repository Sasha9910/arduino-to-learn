/*
 * nome: sinal
 *
 * versão: 1.8
 *
 * Física Aplicada a Computação - Engenharia Informática
 * Departamento de Matemática e Ciências Físicas
 * 
 * Ano lectivo 2025-26
 * 
 * template original: Nuno Pereira | nuno.pereira@ipbeja.pt
 * template modificado: Alejandro Hernandez Hernandez | 27659@stu.ipbeja.pt
 * Hardware: Arduino Uno R3 / nano 33 BLE SENSE e Rev 2 / nano RP2040 Connect
 * 
 * Descrição: i) exemplo de utilização do SerialPlotter
 *           ii) gerador de um sinal sinusoidal com ruído 
 *          iii) envio de 4 valores para o SerialPlotter 
 *           
 * O código foi modificado para se adequar melhor aos padrões internacionais de limpeza
 * respeitar as diretrizes de estilo e oferecer uma visão mais automatizada que ajude
 * os estudantes a compreender melhor as aulas ministradas nas demais disciplinas do semestre.
 * pelo que todas as funções estarão comentadas e em inglês , para aproximar o aluno do idioma de referência ao programar.

* Licença:
 * CC-BY-SA 4.0
*/

// Global variables
float w = 0.2;
float A = 2.;
float Ao = 4.;
float Ro = 1.;
float IR = 100;
float t = 0.;
float dtime = 0.1;
float Lmax;
float Lmin;
float answer = 0;


// Function to input data from the user
void inputData(){
  String values[] = {"A", "w", "Ao", "Ro", "IR"};  
  float *vars[] = {&A, &w, &Ao, &Ro, &IR};  

  for (int i = 0; i < 5; i++ ){
    // Concatenação de Strings com + que às vezes provoca erros no Arduino, portanto, decidimos fazê-lo desta maneira.
    Serial.print("Introduce ");
    Serial.print(values[i]);
    Serial.print(": ");
    while (Serial.available() == 0);
    String input = Serial.readStringUntil('\n');
    *vars[i] = input.toFloat();
    while(Serial.available() > 0) Serial.read();
  }
}

// Function to define the limits based on the input values
void defineLimits(){
  Lmax = A + Ao + Ro;
  Lmin = -A + Ao - Ro;
}

// Setup function to initialize serial communication and get user input
void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Manual Data or Auto Data, 1 or 0");
  while (Serial.available() == 0);
  String input = Serial.readStringUntil("\n");
  answer = input.toFloat();
  if (answer == 0){
    defineLimits();
  }
  else{
    inputData();
    defineLimits();
  }
}

// Function to generate the sinusoidal signal
float matrixSensor ( float A, float w , float t, float Ao){
  return A*sin(w*t) + Ao;

}

// Function to add noise to the signal
float noise(float Ro, float IR){
  return Ro*(float)random(-IR, IR+1)/IR;
}

// Function to combine the signal and noise
float finalSensor (float f, float R){
  return f + R;
  
}

// Function to print the data to the Serial Plotter
  void printData (float Lmax, float Lmin, float f, float fr){
    float values[] = {Lmax, Lmin, f, fr};
    for (int i= 0; i <4; i++ ){
      Serial.print(values[i]);
      if (i<3){Serial.print(" ");}
      else
      Serial.println();
    }
  }

// Loop function to continuously generate and print the signal data
void loop() {
  float f1 = matrixSensor(A, w, t, Ao);
  float R = noise(Ro, IR);
  float fr1 = finalSensor(f1, R);
  printData(Lmax, Lmin, f1, fr1);
  t += dtime;
  delay(10);
}
