# Estudos com o REA

Pasta pessoal de estudos deste fork. Fica fora de `src/`, então não interfere
no código do REA nem no sincronismo com o projeto original
([morluto/rea](https://github.com/morluto/rea)).

```text
estudos/
├── README.md        ← este roteiro
├── prompts.md       ← prompts prontos para usar com seu agente (Claude Code etc.)
├── diario/          ← uma anotação por sessão de estudo (copie TEMPLATE.md)
└── labs/
    ├── Makefile     ← compila cada lab em 4 variantes (-O0, -O2, com e sem símbolos)
    └── src/         ← programas-alvo em C escritos para treinar
```

> ⚖️ Analise apenas o que você tem direito de inspecionar: seus próprios
> programas, estes labs, CTFs e crackmes feitos para isso. Leia o
> [DISCLAIMER.md](../DISCLAIMER.md). Nunca faça commit de binários de terceiros.

## Preparação (uma vez, no seu computador)

1. Node.js 22.19+ / 24.11+ e npm.
2. Instale o REA e registre-o no seu agente:
   ```bash
   npm install --global rea-agents
   rea setup          # mostra o que vai mudar e pede aprovação
   rea providers --json
   ```
3. Para binários nativos, instale o **Ghidra 12.1.x** (gratuito) com o JDK de
   64 bits que ele exige
   e confirme com `rea doctor --provider ghidra --json`. Detalhes em
   [docs/ghidra-provider.md](../docs/ghidra-provider.md).
4. Compilador C (`gcc` ou `clang`) e `make`. Em seguida:

   ```bash
   cd estudos/labs && make
   ```

   Isso gera `labs/bin/` (ignorado pelo git) com 4 versões de cada lab:

   | Variante           | Para quê                                      |
   | ------------------ | --------------------------------------------- |
   | `NOME-O0`          | Sem otimização e com símbolos: o mais fácil   |
   | `NOME-O2`          | Veja como o compilador reescreve o seu código |
   | `NOME-O0-stripped` | Sem nomes de funções, como um programa real   |
   | `NOME-O2-stripped` | O desafio final                               |

Rode os comandos abaixo a partir de `estudos/` (crie a pasta de saídas com
`mkdir -p analises`, que o git ignora).

**Regra de ouro:** tente resolver cada lab olhando só o binário (de preferência
o `-stripped`). Abra o `.c` apenas para conferir a resposta.

## Roteiro

Marque `[x]` conforme for avançando. Ritmo sugerido: 2–4 sessões por semana,
de 45–90 minutos, cada uma registrada em `diario/`.

### Etapa 1 — Fundamentos sem engine nativa (semana 1)

Comece pelo que não exige Ghidra para se acostumar com Evidence, `--json` e
limitações.

- [ ] Ler [docs/cli.md](../docs/cli.md) e [docs/tool-design.md](../docs/tool-design.md).
- [ ] Analisar um app Electron instalado na sua máquina (VS Code, Obsidian…):
      `rea analyze-javascript-application /caminho/app --json > analises/app.json`
      e responder: quais são os processos principal e renderer? Quais canais IPC existem?
- [ ] Exportar um `.har` do DevTools de um site seu e inspecionar com
      `rea inspect-web-network-capture /caminho/sessao.har har --json`.
- [ ] Abrir um banco SQLite de um app seu: `rea inspect-sqlite-database arquivo.sqlite --json`.

### Etapa 2 — Primeiro binário nativo (semana 2)

Labs: `01_ola`, `02_senha`.

- [ ] `rea analyze labs/bin/01_ola-O0 --provider ghidra --json`
- [ ] `rea function labs/bin/01_ola-O0 main --provider ghidra --json` e comparar
      com o `.c`: onde está `soma`? Na versão `-O2` ela ainda existe?
- [ ] `rea search labs/bin/02_senha-O2-stripped "Senha" --provider ghidra --json`,
      depois seguir as referências (`rea xrefs …`) até a função que valida a senha.
- [ ] Descobrir a senha do lab 02 e testar: `./labs/bin/02_senha-O2-stripped <senha>`.

Conceitos a estudar junto: registradores x86-64, convenção de chamada System V
(rdi, rsi, rdx…), stack frame, seções `.text`, `.rodata` e `.data`.

### Etapa 3 — Dados e fluxo de controle (semanas 3–4)

Labs: `03_structs`, `05_estado`.

- [ ] Reconstruir `struct item` (offsets, tipos e `sizeof`) a partir do
      `03_structs-O2-stripped`. Conferir com `offsetof` no `.c`.
- [ ] No `05_estado`, comparar `-O0` e `-O2`: o `switch` virou uma jump table?
      Desenhar a máquina de estados e explicar o que ela aceita.

Conceitos: alinhamento e padding, ponto flutuante (SSE, `xmm0`), loops,
jump tables.

### Etapa 4 — Reconstrução verificável (semanas 5–6)

Lab: `04_checksum`, no estilo dos showcases DX-Ball e TH04
([rea.tools/showcase](https://rea.tools/showcase/)).

- [ ] Pelo `04_checksum-O2-stripped`, escrever sua própria versão de `checksum`
      em `labs/src/04_checksum_reconstruido.c` (sem olhar o original).
- [ ] Provar a equivalência comparando saídas:
      `bash
      for s in a abc Wikipedia "" "texto longo de teste"; do
        diff <(labs/bin/04_checksum-O2 "$s") <(labs/bin/04_checksum_reconstruido-O0 "$s") && echo "ok: $s"
      done
      `
- [ ] Identificar o algoritmo conhecido que ele implementa.

### Etapa 5 — Outros ecossistemas (semanas 7+)

Escolha conforme seu interesse:

- [ ] **Go/Rust:** compile um programa seu e rode
      `rea inspect-go-binary` / `rea inspect-rust-binary`. Quais dependências
      e versões ficaram embutidas?
- [ ] **.NET:** `rea inspect-managed-artifact MeuApp.dll --json`
      ([docs/managed-code-analysis.md](../docs/managed-code-analysis.md)).
- [ ] **Android:** um APK seu ou de exemplo com JADX
      ([docs/android-analysis.md](../docs/android-analysis.md)).
- [ ] **CTF:** resolver um desafio de reversing (picoCTF, crackmes.one) usando o REA
      e escrever o writeup no diário.

### Etapa 6 — Estudar o próprio REA (contínuo)

O código do REA também serve de material de engenharia de software:

- [ ] Ler [docs/architecture.mermaid](../docs/architecture.mermaid) e seguir um
      comando da CLI (ex.: `inspect-sqlite-database`) de `src/` até o adaptador.
- [ ] Entender o padrão `Result` e os erros tipados (procure por `Result` em `src/`).
- [ ] Rodar os testes de uma área: `npm ci && npm run test:local -- tests/<pasta>`.
- [ ] Ler [docs/testing.md](../docs/testing.md) e [CONTRIBUTING.md](../CONTRIBUTING.md);
      escolher uma issue pequena no upstream e abrir um PR.

## Mantendo o fork atualizado

```bash
git remote add upstream https://github.com/morluto/rea.git   # uma vez
git fetch upstream
git checkout main && git merge upstream/main && git push
```

Como tudo daqui fica em `estudos/`, os merges do upstream não geram conflitos.

## Referências rápidas

- Showcases: <https://rea.tools/showcase/>
- Guias oficiais: <https://rea.tools/guides/>
- Lista de ferramentas MCP: [docs/mcp-contracts.md](../docs/mcp-contracts.md)
- Investigação nativa: [docs/native-investigation.md](../docs/native-investigation.md)
