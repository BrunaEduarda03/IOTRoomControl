# IoT Room Control - Controle Inteligente do Laboratório de IoT

Bem-vindo ao repositório do projeto IoT Room Control! 💪

## 💬 Sobre a aplicação 
O projeto "IoT Room Control" tem como objetivo criar um sistema de controle inteligente para o laboratório de Internet das Coisas(IOT). Este sistema permitirá o monitoramento e controle remoto de dispositivos e condições ambientais dentro do laboratório. Além disso, um aplicativo móvel será desenvolvido para facilitar a interação dos usuários com o laboratório.

## :memo: Funcionalidades Principais 

- Monitoramento de Dispositivos IoT: O sistema permite que os usuários monitorem em tempo real os dispositivos IoT instalados no laboratório, como sensores de temperatura, luminosidade, ar-condicionado,cortinas,controle de acesso.
- Controle Remoto: Os usuários podem controlar atuadores e dispositivos remotamente por meio do aplicativo móvel, como ligar ou desligar dispositivos, ajustar configurações e definir programações.
- Alertas e Notificações: O sistema é capaz de enviar alertas e notificações aos usuários em caso de eventos importantes, como a detecção de condições fora dos limites predefinidos.
- Automação Inteligente: O sistema permite criar regras e cenários de automação com base nas condições dos sensores, tornando possível a automação de tarefas rotineiras no laboratório.
- Aplicativo Móvel: Um aplicativo móvel amigável e intuitivo estará disponível tanto para dispositivos Android e iOS quanto para desktop, permitindo que os usuários controlem e monitorem o laboratório a partir de seus smartphones/tablets e computadores.

## 🚀 Tecnologias Utilizadas 
- **Hardware IoT**: ESP32 para controlar sensores, atuadores e protocolo de comunicação mqtt ou http, para enviar dados do hardware para o servidor central.
- **Frontend e Backend**: (A definir) Desenvolvimento integrado usando o React/Nodejs.
- **Aplicativo Móvel**: (A definir) Desenvolvimento integrado usando o React Native.
- **Design e Componentes**: Tailwind CSS para criação de interfaces modernas e responsivas.
- **Banco de Dados**: (A definir) armazenar dados de sensores, informações de configuração e registros de eventos.
- **Implantação**: (A definir) Plataformas de hospedagem em nuvem, como AWS, Azure, Google Cloud, ou hospedagem própria em servidores.
- 
## 🌿 Gerenciamento de Branches com GitFlow 

Nós adotamos a abordagem de gerenciamento de branches GitFlow para organizar o fluxo de trabalho do nosso projeto. Isso significa que utilizamos os branches `main` e `development` como branches principais. O `main` contém o código estável do nosso projeto, enquanto o `development` é onde as novas funcionalidades são desenvolvidas antes de serem mescladas no `main`. Para cada nova funcionalidade, criamos branches de feature a partir do `development`.

Para correções de bugs, criamos branches a partir da `main`. Essa abordagem nos permite manter um fluxo de trabalho organizado, garantindo que as correções de bugs sejam feitas a partir do código estável.

Para saber mais sobre o GitFlow, consulte o [guia oficial](https://nvie.com/posts/a-successful-git-branching-model/) do Vincent Driessen.

## 🤝 Como Contribuir 

1. Faça um clone deste repositório.
2. Crie um branch para as suas alterações: `git checkout -b nome_da_branch`.
3. Faça suas modificações e adições `git add .`.
4. Faça commits das suas mudanças: `git commit -m 'Adiciona novos recursos'`.
5. Faça um push para o seu branch: `git push origin minha-contribuicao`.
6. Abra um pull request neste repositório.

## Documentação e Acompanhamento 🔍

- [Wiki](https://github.com/fullstackclub-labs/fitflow/wiki): Acesse a documentação completa do FitFlow na Wiki.
- [Projeto](https://github.com/users/BrunaEduarda03/projects/1): Acompanhe o progresso do projeto no painel de projetos.
- Issue Tracker: [GitHub Issues](https://github.com/BrunaEduarda03/IOTRoomControl/issues)
- [Commits](https://www.conventionalcommits.org/en/v1.0.0/): cesse a documentação para as mensagens de commits.

## :speaking_head:  Dúvidas ou feedbacks sobre o projeto!

E-mail: [**brunaduda37@gmail.com**](mailto:brunaduda37@gmail.com)

Linkedin: [Bruna Eduarda](https://www.linkedin.com/in/bruna-eduarda-a06a1b18b/)



## Licença 📝

Este projeto é licenciado sob a [Licença MIT](LICENSE).
