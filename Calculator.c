/*
Navn: Alija Cerimagic
Email: acer21@student.aau.dk
Gruppe: B224
Studieretning: Software
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double run_calculator(char *oprd, double *oprnd, double accumulator);
void scan_data(char *scan_operator, double *scan_operand);
double do_next_op(char run_operator, double run_operand, double *do_accumulator);
void flush_input(void);

/* I main calles run_calculator funktionen - denne er i while loop, saa programmet kan stoppes ved input 'q' */

int main(void){
  int BYE = 1;
  char operator;
  double accumulator = 0.0, operand;
  
  while(BYE == 1){
    accumulator = run_calculator(&operator, &operand, accumulator);  
    if(operator == 'q'){
      BYE = 0;
    }
    if(BYE == 1){
      printf("Result so far is %.6lf.\n", accumulator);
    }
  }
  printf("Final result is: %lf\n", accumulator);

  return EXIT_SUCCESS;
}

double run_calculator(char *oprd, double *oprnd, double accumulator){
  double scan_accumulator;

  scan_data(oprd, oprnd);
  scan_accumulator = do_next_op(*oprd, *oprnd, &accumulator);

  return scan_accumulator;
}

/* Input, hvor der tjekkes, om en operand skal inputtes afhaengigt af operatoren */

void scan_data(char *scan_operator, double *scan_operand){
  printf("Enter operator, and an optional operand: ");
  scanf(" %c", scan_operator);

  if(*scan_operator == '+' || *scan_operator == '-' || *scan_operator == '*' || *scan_operator == '/'  || *scan_operator == '^'){
    while(!(scanf("%lf", scan_operand))){
      printf("Enter a valid operand (integer) to proceed: ", *scan_operand, *scan_operator);
      flush_input();
    }
  } else if(*scan_operator == '#' || *scan_operator == '%' || *scan_operator == '!' || *scan_operator == 'q' || *scan_operator == 'r'){
      flush_input();
  } else {
      flush_input();
      scan_data(scan_operator, scan_operand);
  }
}

double do_next_op(char run_operator, double run_operand, double *do_accumulator){
switch(run_operator){
    case '+':
      *do_accumulator = *do_accumulator + run_operand;
      break;
    case '-':
      *do_accumulator = *do_accumulator - run_operand;
      break;
    case '*':
      *do_accumulator = *do_accumulator * run_operand;
      break;
    case '/':
      if(run_operand != 0){
        *do_accumulator = *do_accumulator / run_operand;
      }
      break;
    case '^':
      *do_accumulator = pow(*do_accumulator, run_operand);
      break;
    case '#':
      if(*do_accumulator >= 0){
        *do_accumulator = sqrt(*do_accumulator);
      }
      break;
    case '%':
      *do_accumulator = *do_accumulator * (-1);
      if(*do_accumulator == 0){
        *do_accumulator = 0;
      }
      break;
    case '!':
      if(*do_accumulator != 0){
      *do_accumulator = (1 / *do_accumulator);
      }
      break;
    case 'q':
      break;
    case 'r':
      *do_accumulator = 0;
      break;
    default:
      break;
  }
  return *do_accumulator;
}

/* Denne funktion flusher alle inputs der ikke i forste omgang er gennemarbejdet af programmet, 
men stadigt er lagret. Flusher saa den ikke bearbejder de inputs igen */

void flush_input(void){
  while((getchar()) != '\n');
}
