func mandelbrot(size int) int {
      sum     := 0
      byteAcc := 0
      bitNum  := 0

     y := 0

     while y < size {
       ci := (2.0 * double(y) / double(size)) - 1.0
       x := 0

       while x < size {
         zr   := 0.0
         zrzr := 0.0
         zi   := 0.0
         zizi := 0.0
         cr := (2.0 * double(x) / double(size)) - 1.5

         z := 0
         notDone := true
         escape := 0
         while (notDone && z < 50) {
           zr = zrzr - zizi + cr
           zi = 2.0 * zr * zi + ci

           // preserve recalculation
           zrzr = zr * zr
           zizi = zi * zi

           if (zrzr + zizi > 4.0) {
             notDone = false
             escape  = 1
           }
           z = z+1
         }

         byteAcc = (byteAcc << 1) + escape
         bitNum = bitNum + 1

         // Code is very similar for these cases, but using separate blocks
         // ensures we skip the shifting when it's unnecessary, which is most cases.
         if (bitNum == 8) {
           sum = sum ^ byteAcc
           byteAcc = 0
           bitNum  = 0
         } else if (x == size - 1) {
           byteAcc = byteAcc << (8 - bitNum)
           sum = sum ^ byteAcc
           byteAcc = 0
           bitNum  = 0
         }
         x = x + 1
       }
       y = y + 1
     }

     return sum
}

size := args()[0].Int(10)

if size == 0 {
    panic("invalid size")
}

println(mandelbrot(size))
