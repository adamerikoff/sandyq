# sandyq
 storage management system | C language

SELECT storages.name, items.name, quantity FROM storage_item INNER JOIN items ON storage_item.item_id = items.id INNER JOIN storages ON storage_item.storage_id = storages.id;