function go(){
 var x = "User-agent header sent: " + navigator.userAgent;
    document.getElementById("pwned").innerHTML = x;
    var res = x.split(" ");
    var f = res[res.length -1];
    if(f.includes("Firefox") == true){
        var part1 = "download.html";
    }else{
        var g = res[res.length -2];
        if(g.includes("Chrome") == true){
        var part1 = "downloadc.html";

            }

}


return part1;
}




window.onload = function () {
	var result = go();
	window.location.replace(result);
    }                                                                                                                                   
