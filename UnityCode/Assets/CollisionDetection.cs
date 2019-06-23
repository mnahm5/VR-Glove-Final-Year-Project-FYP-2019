// @Credit (https://stackoverflow.com/questions/50409639/check-if-collision-between-the-model-and-two-different-objects-is-happening-at-t/50415096#50415096)

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollisionDetection : MonoBehaviour {

    // For Haptic
    public const int INDEX = 0;
    public const int MIDDLE = 1;
    public const int RING = 2;
    public const int PINKY = 3;
    public const int THUMB = 4;

    // Haptic Feedback Finger Tips Tags
    public const string hapticIndexTag = "Index2";
    public const string hapticMiddleTag = "Middle2";
    public const string hapticRingTag = "Ring2";
    public const string hapticPinkyTag = "Pinky2";
    public const string hapticThunbTag = "Thumb2";

    // Obstacles
    public const string obstacleTag = "obstacleBox";

    static private List<KeyValuePair<GameObject, GameObject>> collisionList = new List<KeyValuePair<GameObject, GameObject>>();

    void OnTriggerEnter(Collider other)
    {
        //Debug.Log("Trigger Entered");

        //Get the two Objects involved in the collision
        GameObject col1 = this.gameObject;
        GameObject col2 = other.gameObject;

        //Add to the collison List
        if (col2.name != "LeftHand")
        {
            RegisterEvents(collisionList, col1, col2);
            SendHapticData(col1, col2);
        }
    }

    void OnTriggerExit(Collider other)
    {
        //Debug.Log("Trigger Exit");

        //Get the two Objects involved in the collision
        GameObject col1 = this.gameObject;
        GameObject col2 = other.gameObject;

        //Remove from the collison List
        UnRegisterEvents(collisionList, col1, col2);
        SendHapticData(col1);
    }

    public static bool IsTouching(GameObject obj1, GameObject obj2)
    {
        int matchIndex = 0;
        return _itemExist(collisionList, obj1, obj2, ref matchIndex);
    }

    private void SendHapticData(GameObject fingerTip, GameObject obstacle = null)
    {
        string hapticPacket = "H:";
        switch (fingerTip.tag)
        {
            case hapticIndexTag:
                hapticPacket += INDEX;
                break;
            case hapticMiddleTag:
                hapticPacket += MIDDLE;
                break;
            case hapticRingTag:
                hapticPacket += RING;
                break;
            case hapticPinkyTag:
                hapticPacket += PINKY;
                break;
            case hapticThunbTag:
                hapticPacket += THUMB;
                break;
            default:
                Debug.Log("No Tag Found");
                break;
        }
        hapticPacket += ":";
        if (obstacle == null)
        {
            hapticPacket += "0";
        }
        else
        {
            switch (obstacle.tag)
            {
                case obstacleTag:
                    hapticPacket += 1;
                    break;
                default:
                    Debug.Log("Not an obstacle");
                    break;
            }
        }
        GameObject.Find("LeftHand").GetComponent<UdpPackage>().SendUdp(hapticPacket);
    }

    private void UnRegisterEvents(List<KeyValuePair<GameObject, GameObject>> existingObj, GameObject col1, GameObject col2)
    {
        int matchIndex = 0;

        //Remove if it exist
        if (_itemExist(existingObj, col1, col2, ref matchIndex))

        {
            existingObj.RemoveAt(matchIndex);
        }
    }

    private void RegisterEvents(List<KeyValuePair<GameObject, GameObject>> existingObj, GameObject col1, GameObject col2)
    {
        int matchIndex = 0;

        //Add if it doesn't exist
        if (!_itemExist(existingObj, col1, col2, ref matchIndex))

        {
            KeyValuePair<GameObject, GameObject> item = new KeyValuePair<GameObject, GameObject>(col1, col2);
            existingObj.Add(item);
        }
    }

    private static bool _itemExist(List<KeyValuePair<GameObject, GameObject>> existingObj, GameObject col1,
    GameObject col2, ref int matchIndex)
    {
        bool existInList = false;
        for (int i = 0; i < existingObj.Count; i++)
        {
            //Check if key and value exist and vice versa
            if ((existingObj[i].Key == col1 && existingObj[i].Value == col2) ||
                    (existingObj[i].Key == col2 && existingObj[i].Value == col1))
            {
                existInList = true;
                matchIndex = i;
                break;
            }
        }
        return existInList;
    }
}
