let preveiwContainer = document.querySelector('.products-preview');
let previewBox = preveiwContainer.querySelectorAll('.preview');

let amongus = 0;

document.querySelectorAll('.prod .product').forEach(product =>{
  product.onclick = () =>{
    preveiwContainer.style.display = 'flex';
    let name = product.getAttribute('data-name');
    previewBox.forEach(preview =>{
      let target = preview.getAttribute('data-target');
      if(name == target){
        preview.classList.add('active');
        amongus = 1;
        const element = document.querySelector("#appBody");
        element.classList.add("stop-scroll");
      }
    });
  };
});

previewBox.forEach(close =>{
  close.querySelector('.fa-times').onclick = () =>{
    close.classList.remove('active');
    preveiwContainer.style.display = 'none';
    amongus = 0;
    const element = document.querySelector("#appBody");
    element.classList.remove("stop-scroll");
  };
});



  document.addEventListener("click", function(event) {
    if(event.target.closest(".product")) return
    if(amongus == 0) {
    return
    }
    if(event.target.closest(".preview")) return
    previewBox.forEach(box => {
      box.classList.remove('active');
    })
    preveiwContainer.style.display = 'none';
    amongus = 0;
    const element = document.querySelector("#appBody");
    element.classList.remove("stop-scroll");
  })
