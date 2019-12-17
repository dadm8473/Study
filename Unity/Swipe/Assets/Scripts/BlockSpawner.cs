using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockSpawner : MonoBehaviour
{
    // 싱글톤
    public static BlockSpawner instance;

    private void Awake()
    {
        if (BlockSpawner.instance == null)
            BlockSpawner.instance = this;
    }

    void Start()
    {
        
    }

    void Update()
    {
        
    }

    void blockSpawn()
    {

    }
}
