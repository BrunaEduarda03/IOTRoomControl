/**
 * @file macros.h
 * @author William Henrique A. Martins (william.martins@ee.ufcg.edu.br)
 *         <adicionar aqui>
 * @brief 
 * @version 0.1
 * @date 2023-10-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef COMPILE_OPTION
// Caso não tenha especificado este MACRO no compilador,
// Altere aqui para escolher a opção de compilação
#   define COMPILE_OPTION 1
#endif

#if COMPILE_OPTION == 1
#   define COMPILE_MAIN // compila main.cpp
#elif COMPILE_OPTION == 2
#   define COMPILE_DEMO // compila *_Demo.ino
#else
#   define COMPILE_TEST // compila teste do seu módulo
#endif