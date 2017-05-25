# Opencv : Bilinear Interpolation

First, look all pixels one by one and if the pixel value is empty, search left and right side pixel
and add the two values after applying weighted value by how they are distant. If there are no pixels left and right side, then move line up and down and search left and right side like above.

