# medicaosilo


CONTROLE DE ARMAZENAMENTO DE SILO A DISTANCIA

o microcontrolador envia os seguintes dados:
VOLUME DO SILO, calculado com base na altura total do silo decrescido da distancia do sensor ultrasonico (que fica no topo), até a altura do produto armazenado;
ILUMINACAO, envio dos dados do sensor de luminozidade;
ATUALIZAÇÕES, envio da data, hora e minuto (por GMT decrescido de três horas) para informação de quando ocorreu a ultima medição;
EMAIL PAREADO COM O GOOGLE, o processo ocorre atraves do webserver disposto pelo microcontrolador e convertido em SHA1 para criar os nós no banco de dados para cada um dos clientes, desta forma eles podem logar com o google e encontrar as informações hospedadas. 


