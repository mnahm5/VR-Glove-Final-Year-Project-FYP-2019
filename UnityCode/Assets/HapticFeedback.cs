using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class HapticFeedback : MonoBehaviour {

    private UdpPackage udpPackage;

    /* -- Game Objects -- */

    // Haptic GameObjects
    private GameObject hapticIndex;
    private GameObject hapticMiddle;
    private GameObject hapticRing;
    private GameObject hapticPinky;
    private GameObject hapticThumb;

    // Obstacles
    private GameObject box;

    /* -- End Game Objects -- */

    /* -- Tags -- */

    // Obstacles
    public string obstacleTag = "obstacleBox";

    // Haptic Feedback Finger Tips Tags
    public const string hapticIndexTag = "hapticIndex";
    public const string hapticMiddleTag = "hapticMiddle";
    public const string hapticRingTag = "hapticRing";
    public const string hapticPinkyTag = "hapticPinky";
    public const string hapticThunbTag = "hapticThumb";

    /* -- End Tags -- */

    private void Start()
    {
        GameObject leftHand = GameObject.Find("LeftHand");
        udpPackage = leftHand.GetComponent<UdpPackage>();

        GetAllGameObjects();
    }

    private void Update()
    {
        
    }

    private void OnTriggerEnter(Collider other)
    {
        RespondToTrigger();
    }

    private void OnTriggerStay(Collider other)
    {
        
    }

    private void OnTriggerExit(Collider other)
    {
        RespondToTrigger();
    }

    private void RespondToTrigger()
    {
        //string packetData = "H" + CollisionDetection.HapticOutput;
        //udpPackage.SendUdp(packetData);
    }
    
    private void GetAllGameObjects()
    {
        box = GameObject.FindWithTag(obstacleTag);
        //hapticIndex = GameObject.FindWithTag(hapticIndexTag);
        //hapticMiddle = GameObject.FindWithTag(hapticMiddleTag);
        //hapticRing = GameObject.FindWithTag(hapticRingTag);
        //hapticPinky = GameObject.FindWithTag(hapticPinkyTag);
        //hapticThumb = GameObject.FindWithTag(hapticThunbTag);
    }
}
