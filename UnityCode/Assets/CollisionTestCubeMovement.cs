using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollisionTestCubeMovement : MonoBehaviour {

    public float moveSpeed = 0.1f;
    public float turnSpeed = 50f;
    public bool flag = true;

    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        if (Input.GetKey(KeyCode.UpArrow))
            transform.Translate(Vector3.up * moveSpeed * Time.deltaTime);

        if (Input.GetKey(KeyCode.DownArrow))
            transform.Translate(Vector3.down * moveSpeed * Time.deltaTime);

        if (flag)
        {
            if (Input.GetKey(KeyCode.LeftArrow))
                transform.Translate(Vector3.forward * moveSpeed * Time.deltaTime);

            if (Input.GetKey(KeyCode.RightArrow))
                transform.Translate(Vector3.back * moveSpeed * Time.deltaTime);
        }
        else
        {
            if (Input.GetKey(KeyCode.LeftArrow))
                transform.Translate(Vector3.left * moveSpeed * Time.deltaTime);

            if (Input.GetKey(KeyCode.RightArrow))
                transform.Translate(Vector3.right * moveSpeed * Time.deltaTime);
        }

        if (Input.GetKeyDown(KeyCode.LeftControl))
            flag = !flag;
    }
}
