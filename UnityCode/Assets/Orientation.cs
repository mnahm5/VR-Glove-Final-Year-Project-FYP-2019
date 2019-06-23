using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Orientation : MonoBehaviour {

    public GameObject hand;

    private UdpPackage udpPackage;

    private float x = 0.0f, y = 0.0f, z = 0.0f;

    // Use this for initialization
    void Start () {
        GameObject leftHand = GameObject.Find("LeftHand");
        udpPackage = leftHand.GetComponent<UdpPackage>();
    }
	
	// Update is called once per frame
	void Update () {
        hand.transform.localRotation = Quaternion.Euler(udpPackage.pitch, -udpPackage.yaw, udpPackage.roll);
    }
}
