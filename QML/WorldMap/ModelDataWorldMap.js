
var vectMarker = [];

function Marker (posX, posY, idMarker, urlImg)
{
    this.m_posX = posX;
    this.m_posY = posY;
    this.m_idMarker = idMarker;
    this.m_urlImg = urlImg;
}

Marker.prototype.getMarkerXPosition = function()
{
    return this.m_posX;
}

Marker.prototype.getMarkerYPosition = function()
{
    return this.m_posY;
}

Marker.prototype.getIdMarker = function()
{
    return this.m_idMarker;
}




/*var marker1 = new Marker(11, 22);
var marker2 = new Marker(33, 44);

console.log("test JS Class");
console.log(marker1.getMarkerXPosition());
console.log(marker2.getMarkerXPosition());
*/


//var EXPORTED_SYMBOLS = ["currentIdMarker", "currentIdMarker"]

//var currentIdMarker = "";
//var currentUrlImage = "";

/*
function foo() {
  return "foo";
}

var bar = {
  nom : "bar",
  taille : "3"
};

var brol = "brol";
*/



/*export function hello() {
  return "Hello";
}
*/


/*
var Marker = class
{
  constructor(posX, posY)
  {
    this.posX = posX;
    this.posY = posY;
  }
}

var MarkerData = (function ()
{
    //var currentIdMarker = "";
    //var currentUrlImage = "";
/*
    var Marker = class
    {
      constructor(posX, posY)
      {
        this.posX = posX;
        this.posY = posY;
      }
    }
*/
//})

