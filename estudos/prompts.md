# Prompts para usar com o agente + REA

Prompts testados como ponto de partida. Troque os caminhos pelos seus e
adapte. Pedir **evidência** e **o que ainda é incerto** faz o agente separar
fatos observados de suposições.

## Aprender (modo tutor)

```text
Use o REA com o Ghidra para analisar estudos/labs/bin/01_ola-O0. Explique main
linha a linha como se eu estivesse aprendendo assembly x86-64: quais
registradores carregam cada argumento do printf e por quê. Mostre o endereço
de cada instrução que citar.
```

```text
Compare estudos/labs/bin/05_estado-O0 com 05_estado-O2 usando o REA. O que o
compilador mudou na função que contém o switch? Existe jump table? Mostre a
evidência de cada afirmação.
```

## Desafio (sem spoiler)

```text
Estou resolvendo estudos/labs/bin/02_senha-O2-stripped. NÃO me diga a senha.
Use o REA para me dar só a próxima dica: qual função devo olhar e qual
pergunta devo me fazer sobre ela.
```

```text
Escrevi estudos/labs/src/04_checksum_reconstruido.c. Use o REA para comparar
o comportamento com o binário 04_checksum-O2-stripped e aponte divergências
(casos-limite, overflow, tipos), sem reescrever o código por mim.
```

## Dia a dia

```text
Entenda como funciona <recurso> no app <app instalado em /caminho>, mostre
a evidência (arquivos, funções, endereços) e o que ficou como inferência.
Depois sugira como implementar algo parecido no meu projeto em <caminho>.
```

```text
Use o REA para listar as dependências embutidas no binário /caminho/programa
(Go ou Rust) e destaque versões antigas ou com vulnerabilidades conhecidas.
```

```text
Analise o arquivo /caminho/sessao.har com o REA: quais endpoints são chamados,
em que ordem, e quais respostas são maiores. Resuma em uma tabela.
```

## Revisão de estudo

```text
Leia minhas notas em estudos/diario/ e monte 5 perguntas de revisão (tipo
flashcard) sobre os conceitos que eu estudei, com as respostas no final.
```
