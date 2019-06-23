using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HandPosition : MonoBehaviour {
    public GameObject hand;

    public float speedH = 1f;
    public float speedV = 1f;

    private float yaw = 0.0f;
    private float pitch = 0.0f;
    private float z_pos = 0.0f;

    // Use this for initialization
    void Start () {
        //hand.transform.position = new Vector3(0f, 0f, 0f);
        hand.transform.localPosition = new Vector3(0f, 0f, 0f);
    }
	
	// Update is called once per frame
	void Update () {
        pitch  += speedH * Input.GetAxis("Mouse X");
        yaw += speedV * Input.GetAxis("Mouse Y");

        if (Input.GetMouseButtonDown(0)) {
            z_pos += 0.01f;
        }
        else if (Input.GetMouseButtonDown(1)) {
            z_pos -= 0.01f;
        }

        Vector3 target = new Vector3(pitch*-0.001f, yaw*0.001f, z_pos);
        hand.transform.localPosition = Vector3.Slerp(hand.transform.localPosition, target, Time.deltaTime * 30);
        //string current = string.Format("{0}", Input.GetAxis("Mouse X"));
        //Debug.Log(current);
    }
}
