import QtQuick 2.0

// SPRITE Animation
Rectangle
{
    id: spriteAnimation
    width: parent.width / 25
    height: parent.width / 25 + ((parent.width / 25) / 3)
    color: "transparent"

    function spriteRestart()
    {
        sprite.restart();
        console.log("sprite restart");
    }

    Behavior on x
    {
        NumberAnimation
        {
            id: animationSpriteX;
            target: spriteAnimation;
            properties: "x";
            duration: 500;
            easing.type:Easing.Linear;
         }
    }
    Behavior on y
    {
        NumberAnimation
        {
            id: animationSpriteY;
            target: spriteAnimation;
            properties: "y";
            duration: 500;
            easing.type:Easing.Linear;
         }
    }


    AnimatedSprite
    {
        id: sprite

        source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/SpriteAnimation/SpriteAnimation50x66Right.png"
        frameWidth: 33
        frameHeight: 50
        frameCount: 2
        frameDuration: 400
        //anchors.centerIn: parent
        width: parent.width
        height: parent.height
        interpolate: false
    }

    MouseArea
    {
        width: parent.width
        height: parent.height
        anchors.fill: parent

        onPressed:
        {
            console.log("click on Sprite hero");
            //sprite.source = "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/SpriteAnimation/SpriteAnimation50x66Left.png";
        }

        onDoubleClicked:
        {
            flickMapArea.state = "FOCUS_ON_HERO";
        }
    }

    // Move the hero to the click position
    function moveHero(xPos, yPos, zoomLevel)
    {
        // Change the sprite direction
        if(xPos / zoomLevel >= spriteAnimation.x)
        {
            sprite.source = "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/SpriteAnimation/SpriteAnimation50x66Right.png";
        }
        else
        {
            sprite.source = "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/SpriteAnimation/SpriteAnimation50x66Left.png";
        }

        // Set the position of the Sprite animation component
        spriteAnimation.x = xPos / zoomLevel - spriteAnimation.width /2;
        spriteAnimation.y = yPos / zoomLevel - spriteAnimation.height /2;
    }
}
