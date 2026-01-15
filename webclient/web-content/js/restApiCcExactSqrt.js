function restApiCcExactSqrt(){
  $("#resultCc").html("Ergebniss von C++: ")
  $("#sendenCc").on("click", function(e){
      var rad = $("#radicandCc").val()
      console.log("Send to CC Rest API: " + rad);
      fetch("http://localhost:8081/exactSquareRoot/" + rad)
        .then(response => {
        if (!response.ok) {
            throw new Error('Netzwerk-Antwort war nicht ok');
        }
        return response.json();
        })
        .then(data => {
          console.log("Result from C++ Rest API: " + JSON.stringify(data));
          var length = data.length;
          if(length == 0){
            $("#resultCc").html(
              "Ergebnis: " + "&radic;<span style=\"text-decoration: overline\">" + 
              rad + 
              "</span>"
            );
          } else {
            if(length == 1){
              if (data[0].multiplicator == -1){
                $("#resultCc").html(
                  "Ergebnis: " + data[0].squareRoot + 
                  "</span>"
                );
              }else{
                var erg = "| " + data[0].multiplicator + 
                  "&times;&radic;<span style=\"text-decoration: overline\">" + 
                  data[0].squareRoot + 
                  "</span>" + " | ";
                $("#resultCc").html(
                  "Ergebnis: " +  erg
                )
              }
            }else{
              var collectRes = "";
              for(const item of data){
                var erg = "| " + item.multiplicator + 
                  "&times;&radic;<span style=\"text-decoration: overline\">" + 
                  item.squareRoot + 
                  "</span>" + " | ";
                  collectRes = collectRes + erg;
              }
              $("#resultCc").html(
                  "Ergebnis: " +  collectRes
                )
            }
          }
          })
        .catch(error => {
          document.getElementById('error').textContent = 'Fehler: ' + error;
        });
  })
}