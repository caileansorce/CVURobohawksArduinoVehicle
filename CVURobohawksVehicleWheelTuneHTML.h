R"====(

<html>

<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, user-scalable=no, minimum-scale=1.0, maximum-scale=1.0" />

    <style>
        body {
            overflow: hidden;
            padding: 0;
            margin: 0;
            background-color: #BBB;
            /* border: 5px solid black */
        }

        #title {
            position: relative;
            top: 8px;
            width: 100%;
            padding: 10px;
            text-align: center;
            font-size: 18pt;
        }

        #sliders {
            position: absolute;
            /* padding: 10px; */
            width: 100%;
            /* bottom: 150px; */
            top: 70px;
            text-align: center;
            /* border: 1px solid grey; */
        }


        span#left-wheel {
            position: absolute;
            padding: 0px;
            width: 100px;
            height: 100%;
            transform: translate(-50%, 0);
            left: 30%;
            /* border: 1px solid green; */
        }

        span#right-wheel {
            position: absolute;
            padding: 0px;
            width: 100px;
            height: 100%;
            transform: translate(-50%, 0);
            left: 70%;
            /* border: 1px solid green; */
        }

        #left-wheel-slide,
        #right-wheel-slide {
            position: absolute;
            width: calc(100vh - 300px);
            transform: translate(-50%, -50%) rotate(270deg);
            left: 50%;
            top: calc(50vh - 100px);
            /* width: 100%; */


            appearance: none;
            height: 15px;
            background: rgb(153, 0, 0);
            outline: none;
            opacity: 0.7;
            -webkit-transition: .2s;
            transition: opacity .2s;
        }

        #left-wheel-slide::-webkit-slider-thumb,
        #right-wheel-slide::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 35px;
            height: 35px;
            border-radius: 50%;
            background: #000000;
            cursor: pointer;
        }

        #left-wheel-slide::-moz-range-thumb,
        #right-wheel-slide::-moz-range-thumb {
            width: 35px;
            height: 35px;
            border-radius: 50%;
            background: #000000;
            cursor: pointer;
        }

        span#left-wheel-value,
        span#right-wheel-value {
            position: absolute;
            width: 110px;
            transform: translate(-50%, 0);
            top: 0;
            left: 50%;
            text-align: center;
            font-size: 14pt;
            /* border: 1px solid blue; */
        }


        #left-wheel-val-field,
        #right-wheel-val-field {
            position: relative;
            width: 8ch;
            font-size: 14pt;
        }


        #btns {
            position: absolute;
            bottom: 20px;
            width: 100%;
            height: 50px;
            padding: 5px;
            text-align: center;
            /* border: 1px solid cyan; */
        }

        #save-btn {
            background-color: rgb(185, 0, 0);
            font-size: 14pt;
            font-weight: bold;
        }

        #main-page-link {
            font-size: 14pt;
        }
    </style>
</head>

<body>
    <h3 id="title">Wheel Error Adjustment</h3>

    <div id="sliders">
        <span id="left-wheel">
            <span id="left-wheel-value"><input type="number" , id="left-wheel-val-field"> uS</span>
            <input type="range" , id="left-wheel-slide">
        </span>
        <span id="right-wheel">
            <span id="right-wheel-value"><input type="number" , id="right-wheel-val-field"> uS</span>
            <input type="range" , id="right-wheel-slide">
        </span>
    </div>
    <div id="btns">
        <button id="save-btn" , onclick="confirmSave()">Save Mid Positions</button>
        </br>
        </br>
        <a href="./CVURobohawksVehicleControlHTML.html" id="main-page-link">Return to control page</a>
    </div>


    <script>
        var maxWheelVal = "500";
        var minWheelVal = "-500";

        var rightWheelSlider = document.getElementById("right-wheel-slide");
        var rightWheelVal = document.getElementById("right-wheel-val-field");
        var leftWheelSlider = document.getElementById("left-wheel-slide");
        var leftWheelVal = document.getElementById("left-wheel-val-field");

        leftWheelSlider.min = rightWheelSlider.min = leftWheelVal.min = rightWheelVal.min = minWheelVal;
        leftWheelSlider.max = rightWheelSlider.max = leftWheelVal.max = rightWheelVal.max = maxWheelVal;
        getInitialPositions();


        leftWheelSlider.addEventListener("input", updateElValue(leftWheelVal), false);
        rightWheelSlider.addEventListener("input", updateElValue(rightWheelVal), false);
        leftWheelVal.addEventListener("input", updateElValue(leftWheelSlider), false);
        rightWheelVal.addEventListener("input", updateElValue(rightWheelSlider), false);


        function updateElValue(elToUpdate) {
            return function _updateElValue(evt) {
                elToUpdate.value = evt.currentTarget.value;
            }
        }


        function confirmSave() {
            if (confirm("Are you sure you want to save?" +
                "       Saving writes to flash memory, which can only be re-written a limited number of times.")) {
                var xhr = new XMLHttpRequest();
                xhr.open('PUT', "./saveWheelErrors")
                xhr.send();

                console.log("save info");
            } else {
                console.log("not saving");
            }
        }

        function getInitialPositions() {
            var xhr = new XMLHttpRequest();

            xhr.onreadystatechange = function () {
                if (xhr.readyState === xhr.DONE && xhr.status === 200) {
                    console.log(xhr.response);
                    var response = new URLSearchParams(xhr.responseText);

                    leftWheelSlider.value = leftWheelVal.value = response.get("l");
                    rightWheelSlider.value = rightWheelVal.value = response.get("r");
                }
            }
            xhr.open('GET', './wheelErrors');
            xhr.send();
        }


        var prevLeft = 0;
        var prevRight = 0;
        var newLeft = 0;
        var newRight = 0;

        setInterval(function () {
            newLeft = leftWheelVal.value;
            newRight = rightWheelVal.value;
            if (newLeft != prevLeft || newRight != prevRight) {
                var xhr = new XMLHttpRequest();
                xhr.open('PUT', "./wheelErrors.html?l=" + newLeft + "&r=" + newRight)
                xhr.send();
                prevLeft = newLeft;
                prevRight = newRight;
            }
        }, 1 / 10 * 1000);

    </script>
</body>

</html>

)===="