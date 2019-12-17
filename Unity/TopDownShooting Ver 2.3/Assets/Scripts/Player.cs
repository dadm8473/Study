using UnityEngine;
using System.Collections;

[RequireComponent (typeof (PlayerController))]
[RequireComponent (typeof (GunController))]
public class Player : LivingEntity {

	public float moveSpeed = 5;
     
	public Crosshairs crosshairs;

	Camera viewCamera;
	PlayerController controller;
	GunController gunController;

    public bool a_weappon_1;
    public bool a_weappon_2;
    public bool a_weappon_3;
    public bool a_weappon_4;
    public bool a_weappon_5;

    public GameObject[] weapons;
    public GameObject[] weaponCover;

    public Spawner spawner;

    protected override void Start () {
		base.Start ();
	}

	void Awake() {
		controller = GetComponent<PlayerController> ();
		gunController = GetComponent<GunController> ();
		viewCamera = Camera.main;
		FindObjectOfType<Spawner> ().OnNewWave += OnNewWave;
	}

	void OnNewWave(int waveNumber) {
		health = startingHealth;
		gunController.EquipGun (waveNumber - 1);
	}

    void Update()
    {
        // Movement input
        Vector3 moveInput = new Vector3(Input.GetAxisRaw("Horizontal"), 0, Input.GetAxisRaw("Vertical"));
        Vector3 moveVelocity = moveInput.normalized * moveSpeed;
        controller.Move(moveVelocity);

        // Look input
        Ray ray = viewCamera.ScreenPointToRay(Input.mousePosition);
        Plane groundPlane = new Plane(Vector3.up, Vector3.up * gunController.GunHeight);
        float rayDistance;

        if (groundPlane.Raycast(ray, out rayDistance))
        {
            Vector3 point = ray.GetPoint(rayDistance);
            //Debug.DrawLine(ray.origin,point,Color.red);
            controller.LookAt(point);
            crosshairs.transform.position = point;
            crosshairs.DetectTargets(ray);
            if ((new Vector2(point.x, point.z) - new Vector2(transform.position.x, transform.position.z)).sqrMagnitude > 1)
            {
                gunController.Aim(point);
            }
        }

        switch(spawner.currentWaveNumber)
        {
            case 0:
                Debug.Log("current 0");
                break;
            case 1:
                a_weappon_1 = true;
                break;
            case 2:
                a_weappon_2 = true;
                break;
            case 3:
                a_weappon_3 = true;
                break;
            case 4:
                a_weappon_4 = true;
                break;
            case 5:
                a_weappon_5 = true;
                break;
        }


        // Weapon input
        if (Input.GetMouseButton(0))
        {
            gunController.OnTriggerHold();
        }
        if (Input.GetMouseButtonUp(0))
        {
            gunController.OnTriggerRelease();
        }
        if (Input.GetKeyDown(KeyCode.R))
        {
            gunController.Reload();
        }

        if(Input.GetKeyDown(KeyCode.F1))
        {
            spawner.skipWave();
        }

        if (transform.position.y < -10)
        {
            TakeDamage(health);
        }

        if (a_weappon_1)
        {
            if (Input.GetKeyDown(KeyCode.Alpha1))
            {
                gunController.EquipGun(0);
                Debug.Log("click");
            }

            weapons[0].SetActive(true);
        }

        if (a_weappon_2)
        {
            if (Input.GetKeyDown(KeyCode.Alpha2))
            {
                gunController.EquipGun(1);
            }

            weapons[1].SetActive(true);
        }

        if (a_weappon_3)
        {
            if (Input.GetKeyDown(KeyCode.Alpha3))
            {
                gunController.EquipGun(2);
            }

            weapons[2].SetActive(true);
        }

        if (a_weappon_4)
        {
            if (Input.GetKeyDown(KeyCode.Alpha4))
            {
                gunController.EquipGun(3);
            }

            weapons[3].SetActive(true);
        }

        if (a_weappon_5)
        {
            if (Input.GetKeyDown(KeyCode.Alpha5))
            {
                gunController.EquipGun(4);
            }

            weapons[4].SetActive(true);
        }
    }

	public override void Die ()
	{
		AudioManager.instance.PlaySound ("Player Death", transform.position);
		base.Die ();
	}
		
}
