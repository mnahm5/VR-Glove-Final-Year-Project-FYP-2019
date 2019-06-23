using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GripSimulation : MonoBehaviour {

    private int PUSH = 1;
    private int PULL = 0;
    private int OFF = 2;
    private float waitTime = 1.0f;

    private bool[] collidingWith = new bool[5];
    private bool[] stopping = new bool[5];

    private IEnumerator coRoutineForTurnOffGrip;

    // Game Objects
    private GameObject[,] fingerJoints;
    private GameObject Box;

    // Tags
    private static readonly string[,] fingerJointTags = { 
        { "Index0" , "Index1" , "Index2" },
        { "Middle0" , "Middle1" , "Middle2" },
        { "Ring0" , "Ring0" , "Ring0" },
        { "Pinky0" , "Pinky1" , "Pinky2" },
        { "Thumb0" , "Thumb1" , "Thumb2" },
    };
    private const string boxTag = "obstacleBox";

    private UdpPackage udpPackage;

    // Use this for initialization
    void Start () {
        GameObject leftHand = GameObject.Find("LeftHand");
        udpPackage = leftHand.GetComponent<UdpPackage>();

        fingerJoints = new GameObject[5, 3];
        for (int fingerNumber = 0; fingerNumber < 5; fingerNumber++)
        {
            for (int jointNumber = 0; jointNumber < 3; jointNumber++)
            {
                fingerJoints[fingerNumber, jointNumber] = GameObject.FindWithTag(fingerJointTags[fingerNumber, jointNumber]);
            }
        }
        Box = GameObject.FindWithTag(boxTag);
    }
	
	// Update is called once per frame
	void Update () {

    }

    private void OnTriggerEnter(Collider other)
    {
        CheckForGrip();
    }

    private void OnTriggerStay(Collider other)
    {

    }

    private void OnTriggerExit(Collider other)
    {
        CheckForGrip();
    }

    private void CheckForGrip()
    {
        // Do appropriate checks here using the isTouching Function in the Collision Detection
        CheckForGripFinger(CollisionDetection.INDEX);
        CheckForGripFinger(CollisionDetection.THUMB);
    }

    private IEnumerator CoRoutineForTurnOffGrip(float waitTime, int finger)
    {
        yield return new WaitForSeconds(waitTime);
        Debug.Log("Started CoRoutine");
        if (!collidingWith[finger])
        {
            SendGripPacket(finger, OFF);
        }
        else
        {
            Debug.Log("Did not send off packet for " + finger);
        }
    }

    private void CheckForGripFinger(int finger)
    {
        CheckIsTouching(finger);
        if (!stopping[finger] && collidingWith[finger])
        {
            SendGripPacket(finger, PUSH);
            stopping[finger] = true;
        }
        else if (stopping[finger] && !collidingWith[finger])
        {
            SendGripPacket(finger, PULL);
            stopping[finger] = false;
            coRoutineForTurnOffGrip = CoRoutineForTurnOffGrip(waitTime, finger);
            StartCoroutine(coRoutineForTurnOffGrip);
        }
    }

    private void CheckIsTouching(int finger)
    {
        collidingWith[finger] =
            CollisionDetection.IsTouching(fingerJoints[finger, 0], Box) ||
            CollisionDetection.IsTouching(fingerJoints[finger, 1], Box) ||
            CollisionDetection.IsTouching(fingerJoints[finger, 2], Box);
    }

    private void SendGripPacket(int finger, int cmd)
    {
        string gripPacket = "G:" + finger + ":" + cmd;
        udpPackage.SendUdp(gripPacket);
    }
}
