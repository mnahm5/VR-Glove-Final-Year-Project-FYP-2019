using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraControl : MonoBehaviour {
    public GameObject mainCamera;

    private float yaw = 42.507f;
    private float pitch = -215.011f;
    private float roll = -20.078f;


    // Use this for initialization
    void Start () {
        mainCamera.transform.localPosition = mainCamera.transform.position;
        mainCamera.transform.localRotation = mainCamera.transform.rotation;
    }
	
	// Update is called once per frame
	void Update () {
        if (Input.GetKey("w")) {
            mainCamera.transform.position = mainCamera.transform.position + new Vector3(0,0,-0.1f);
        }

        else if (Input.GetKey("s")) {
            mainCamera.transform.position = mainCamera.transform.position + new Vector3(0, 0, 0.1f);
        }

        if (Input.GetKey("d")) {
            mainCamera.transform.position = mainCamera.transform.position + new Vector3(-0.1f, 0, 0);
        }

        else if (Input.GetKey("a")) {
            mainCamera.transform.position = mainCamera.transform.position + new Vector3(0.1f, 0, 0);
        }

        if (Input.GetKey("r")){ yaw += 0.5f; }

        else if (Input.GetKey("f")){ yaw -= 0.5f; }

        if (Input.GetKey("t")){ pitch += 0.5f; }

        else if (Input.GetKey("g")){ pitch -= 0.5f; }

        if (Input.GetKey("y")){ roll += 0.5f; }

        else if (Input.GetKey("h")){ roll -= 0.5f; }

        //Quaternion target = Quaternion.Euler(yaw, pitch, roll);
        //mainCamera.transform.rotation =  Quaternion.Slerp(mainCamera.transform.rotation, target, Time.deltaTime * 40);
    }
}
