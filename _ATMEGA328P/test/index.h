const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style type="text/css">
.button {
  background-color: #4CAF50; /* Green */
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
}
</style>
<body style="background-color: #f9e79f ">
<center>
<div>
<h1>ESP8266 WEBSERVER</h1>
  <a href='/ledred'><button class="button" onclick="send(1)">LED RED</button>
  <a href='/ledgreen'><button class="button" onclick="send(2)">LED GREEN</button>
  <a href='/ledblue'><button class="button" onclick="send(3)">LED BLUE</button><BR>
</div>
 <br>
<div>
<h2>
  POINT : <span id="point_val">0</span><br><br>
</h2>
</div>
<script>
setInterval(function() 
{
  getData();
}, 100); 
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("point_val").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "adcread", true);
  xhttp.send();
}
</script>
</center>
</body>
</html>
)=====";
