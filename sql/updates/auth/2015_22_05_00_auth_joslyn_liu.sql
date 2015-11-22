-- reload command for Chat Filter

INSERT INTO `rbac_permissions` 
	(`id`, 
	`name`
	)
	VALUES
	('1590', 
	'Command: reload chat_filter'
	);

INSERT INTO `rbac_linked_permissions` 
	(`id`, 
	`linkedId`
	)
	VALUES
	('192', 
	'1590'
	);
