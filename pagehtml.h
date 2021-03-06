const char paginahtml[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt" id="idHTML">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="favicon" href="favicon.ico" />
        <title>Medidor de Volume</title>
    </head>

    <body id="idBody">
        <chips class="chips">
            <form action="/get">
                <br>
                </br>
                Parear email com Google
                <br>
                <input type="text" name="input1" class="email">
                <br>
                <input type="submit" value="Conectar" id="login" class="btn-text"></input>
                

                <div class="modal">
                </div>
            </form>
        </chips>
    </body>

    <style>

        @import url('https://fonts.googleapis.com/css2?family=Comfortaa:wght@500&display=swap');        *{
          margin: 0px;
          padding: 0px;
        }
        html, body{
            background: #A5BEFF;
            font-family: 'Comfortaa', cursive;            
            padding: 40px 0;
            color: rgb(12, 15, 82);
            font-size: 25px;
            margin: 20px;
            transition: 1s ease-in-out; 
        }

        ::-webkit-scrollbar {
            width: 0px;
            width: 0px;
            background: #111; /* make scrollbar transparent */
        }


        .container {
            margin: 0 auto;
            width: 400px;
            
        }

        .triangle-up {
          width: 0;
          height: 0;
          border-style: solid;
          border-width: 0 150px 100px 150px;
          border-color: transparent transparent #FAF4C4 transparent;
          top: 20%;
          left: 30px;
          position: relative;
          transition: 1s ease-in-out;
          transition: 1s ease-in-out; 
        }
        .square{
          width: 300px;
          height: 100px;
          position: relative;
          top: 20%;
          left: 30px;
          background: #FAF4C4;
          transition: 1s ease-in-out;
        }
        .part{
          position: absolute;
          top: 0;
          left: 0;
          right: 0;
          bottom: 0;
          background: #1a237d;
          transform: scaleY(0.2);
          transform-origin: center bottom;
          transition: 1s ease-in-out;        
        }

        .chips {
            top: 0%;
            left: 0%;
            height: 100%;
            width: 100%;
            position: fixed;
            transition: 0.8s;
            background: #14221c;
            -webkit-backdrop-filter:saturate(180%) blur(20px);
            backdrop-filter: blur(1rem);
            visibility: visible;
            overflow-y: auto; 
            display: flex;
            background-color: #00a7ee;
            justify-content: center;
            z-index: 5;

        }

        .btn-text {
            position: relative;
            border: #8e5eff57;
            border-width: 2px;
            border-style: solid;
            height: 40px;
            width: 160px;
            outline: none;
            font-size: 18px;
            z-index: 2;
            margin-top: 5px;
            margin-left: 5px;
            background: #ffffffa6;
            color: #5062b1;
            border-radius: 15px;

        }

        .btn-text:active {
            background-color: #05648d;
        }

        .logout{
            top: 13px;
            right: 30px;
            position: absolute;
            font-size: 16px;
            padding: 5px 10px;
        }


        .email{
            position: relative;
            border: #8e5eff57;
            border-width: 2px;
            border-style: solid;
            height: 20px;
            width: 300px;
            padding: 5px;
            padding-top: 8px;
            padding-bottom: 6px;
            padding-left: 15px; 
            outline: none;
            font-size: 18px;
            z-index: 2;
            margin-top: 5px;
            margin-left: 5px;
            background: #ffffff52;
            color: #3d259b;
            border-radius: 15px;
            }
            ::placeholder { /* Recent browsers */
                text-transform: none;
                color: #857ec2;
            }

      </style>
</html>
)=====";
