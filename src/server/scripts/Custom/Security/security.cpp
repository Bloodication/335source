class dementia_remove_update : public PlayerScript
{
public:
	dementia_remove_update() : PlayerScript("dementia_remove_update") {}

	void OnUpdateZone(Player* pPlayer, uint32 newZone, uint32 newArea)
	{
		// Remove Dementia on updating zone
		if (pPlayer->HasAura(41406))
			pPlayer->RemoveAura(41406);

	}
};


	class dementia_remove_login : public PlayerScript
	{
	public:
		dementia_remove_login() : PlayerScript("dementia_remove_login") {}

		void OnLogin(Player* player)
		{
			// Remove Dementia on login
			if (player->HasAura(41406))
				player->RemoveAura(41406);
		}
};

	void AddSC_Dementia_Remove_Scripts()
{
	new dementia_remove_login();
	new dementia_remove_update();
}

