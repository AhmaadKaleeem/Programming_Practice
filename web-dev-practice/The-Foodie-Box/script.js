                          
function addFeaturedItem(imageSrc, caption) {
    const gridContainer = document.querySelector('.grid-container');
    const newItem = document.createElement('div');
    newItem.classList.add('grid-item');
  
    newItem.innerHTML = `
      <img src="${imageSrc}" alt="${caption}">
      <p>${caption}</p>
    `;
  
    gridContainer.appendChild(newItem);
  }
  
  function addFeaturedItemPrompt() {
    const imageSrc = prompt('Enter the image URL:');
    const caption = prompt('Enter the caption:');
    if (imageSrc && caption) {
      addFeaturedItem(imageSrc, caption);
    }
  }
  

  function editFeaturedItem(index, newCaption) {
    const gridItems = document.querySelectorAll('.grid-item');
    if (index >= 0 && index < gridItems.length) {
      const item = gridItems[index];
      item.querySelector('p').textContent = newCaption;
    }
  }
  

  function editFeaturedItemPrompt() {
    const index = parseInt(prompt('Enter the index of the item to edit (0, 1, 2, ...):'), 10);
    const newCaption = prompt('Enter the new caption:');
    if (!isNaN(index) && newCaption) {
      editFeaturedItem(index, newCaption);
    }
  }
  

  function removeFeaturedItem(index) {
    const gridItems = document.querySelectorAll('.grid-item');
    if (index >= 0 && index < gridItems.length) {
      const item = gridItems[index];
      item.parentNode.removeChild(item);
    }
  }
  

  function removeFeaturedItemPrompt() {
    const index = parseInt(prompt('Enter the index of the item to remove (0, 1, 2, ...):'), 10);
    if (!isNaN(index)) {
      removeFeaturedItem(index);
    }
  }
  