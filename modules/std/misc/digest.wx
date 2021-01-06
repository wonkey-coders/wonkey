
Namespace std.digest

'Thanks to mx2 user Jesse for converting the original bmx code by bmx user Yan!

Private

Function Hex:String(val:UInt)
	Local hex:=("00000000"+stringio.ULongToString(val,16)).Right(8)
	Return hex
End Function
 
Function Rol:UInt(val:UInt, shift:Int)
	Return (val Shl shift) | (val Shr (32 - shift))
End Function
 
Function Ror:UInt(val:UInt, shift:Int)
	Return (val Shr shift) | (val Shl (32 - shift))
End Function

'Todo: should this be an operator?
Function UShr:UInt(val:UInt, shift:Int)
	Return val Shr shift
End
 
Function LEHex:String(val:UInt)
	Local out:String = Hex(val)
	Return out.Slice(6,8) + out.Slice(4,6) + out.Slice(2,4) + out.Slice(0,2)
End Function
 
Public

Function MD5:String( in:String )
	
	Local h0:Int = $67452301, h1:Int = $EFCDAB89, h2:Int = $98BADCFE, h3:Int = $10325476
    
	Local r:Int[] = New Int[](
		7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
		5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
		4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
		6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21)
                
	Local k:Int[] = New Int[](
		$D76AA478, $E8C7B756, $242070DB, $C1BDCEEE, $F57C0FAF, $4787C62A,
		$A8304613, $FD469501, $698098D8, $8B44F7AF, $FFFF5BB1, $895CD7BE,
		$6B901122, $FD987193, $A679438E, $49B40821, $F61E2562, $C040B340,
		$265E5A51, $E9B6C7AA, $D62F105D, $02441453, $D8A1E681, $E7D3FBC8,
		$21E1CDE6, $C33707D6, $F4D50D87, $455A14ED, $A9E3E905, $FCEFA3F8,
		$676F02D9, $8D2A4C8A, $FFFA3942, $8771F681, $6D9D6122, $FDE5380C,
		$A4BEEA44, $4BDECFA9, $F6BB4B60, $BEBFBC70, $289B7EC6, $EAA127FA,
		$D4EF3085, $04881D05, $D9D4D039, $E6DB99E5, $1FA27CF8, $C4AC5665,
		$F4292244, $432AFF97, $AB9423A7, $FC93A039, $655B59C3, $8F0CCC92,
		$FFEFF47D, $85845DD1, $6FA87E4F, $FE2CE6E0, $A3014314, $4E0811A1,
		$F7537E82, $BD3AF235, $2AD7D2BB, $EB86D391)
                
	Local intCount:Int = (((in.Length + 8) Shr 6) + 1) Shl 4
  	Local data:Int[] = New Int[intCount]
  
	For Local c:Int=0 Until in.Length
		data[c Shr 2] = data[c Shr 2] | ((in[c] & $FF) Shl ((c & 3) Shl 3))
  	Next
  	
	data[in.Length Shr 2] = data[in.Length Shr 2] | ($80 Shl ((in.Length & 3) Shl 3)) 
	data[data.Length - 2] = (Long(in.Length) * 8) & $FFFFFFFF
	data[data.Length - 1] = (Long(in.Length) * 8) Shr 32
  
	For Local chunkStart:Int=0 Until intCount Step 16
		
		Local a:Int = h0, b:Int = h1, c:Int = h2, d:Int = h3
    
	    For Local i:Int=0 To 15
		    
			Local f:Int = d ~ (b & (c ~ d))
			Local t:Int = d
      
			d = c ; c = b
			b = Rol((a + f + k[i] + data[chunkStart + i]), r[i]) + b
			a = t
		Next
    
		For Local i:Int=16 To 31
			
			Local f:Int = c ~ (d & (b ~ c))
      		Local t:Int = d
 
			d = c ; c = b
			b = Rol((a + f + k[i] + data[chunkStart + (((5 * i) + 1) & 15)]), r[i]) + b
			a = t
		Next
    
		For Local i:Int=32 To 47
			
			Local f:Int = b ~ c ~ d
			Local t:Int = d
      
			d = c ; c = b
			b = Rol((a + f + k[i] + data[chunkStart + (((3 * i) + 5) & 15)]), r[i]) + b
			a = t
		Next
    
		For Local i:Int=48 To 63
			
			Local f:Int = c ~ (b | ~d)
			Local t:Int = d
      
			d = c ; c = b
			b = Rol((a + f + k[i] + data[chunkStart + ((7 * i) & 15)]), r[i]) + b
			a = t
		Next
    
		h0 += a 
		h1 += b
		h2 += c 
		h3 += d

	Next
  
	Return (LEHex(h0) + LEHex(h1) + LEHex(h2) + LEHex(h3)).ToLower()

End
 
Function SHA1:String( in:String )
	
	Local h0:Int = $67452301, h1:Int = $EFCDAB89, h2:Int = $98BADCFE, h3:Int = $10325476, h4:Int = $C3D2E1F0
  
	Local intCount:Int = (((in.Length + 8) Shr 6) + 1) Shl 4
	Local data:Int[] = New Int[intCount]
  
	For Local c:Int=0 Until in.Length
		data[c Shr 2] = (data[c Shr 2] Shl 8) | (in[c] & $FF)
 	Next
 	
	data[in.Length Shr 2] = ((data[in.Length Shr 2] Shl 8) | $80) Shl ((3 - (in.Length & 3)) Shl 3) 
	data[data.Length - 2] = (Long(in.Length) * 8) Shr 32
	data[data.Length - 1] = (Long(in.Length) * 8) & $FFFFFFFF
  
	For Local chunkStart:Int=0 Until intCount Step 16
		
		Local a:Int = h0, b:Int = h1, c:Int = h2, d:Int = h3, e:Int = h4
 
		Local w := data.Slice(chunkStart,chunkStart+16).Resize(80)
    
		For Local i:Int=16 To 79
			w[i] = Rol(w[i - 3] ~ w[i - 8] ~ w[i - 14] ~ w[i - 16], 1)
		Next
    
		For Local i:Int=0 To 19
			Local t:Int = Rol(a, 5) + (d ~ (b & (c ~ d))) + e + $5A827999 + w[i]
      
			e = d ; d = c
			c = Rol(b, 30)
			b = a ; a = t
		Next
    
		For Local i:Int=20 To 39
			Local t:Int = Rol(a, 5) + (b ~ c ~ d) + e + $6ED9EBA1 + w[i]
      
			e = d ; d = c
			c = Rol(b, 30)
			b = a ; a = t
		Next
    
		For Local i:Int=40 To 59
			Local t:Int = Rol(a, 5) + ((b & c) | (d & (b | c))) + e + $8F1BBCDC + w[i]
      
			e = d ; d = c
			c = Rol(b, 30)
			b = a ; a = t
		Next
 
		For Local i:Int=60 To 79
			Local t:Int = Rol(a, 5) + (b ~ c ~ d) + e + $CA62C1D6 + w[i]
      
			e = d ; d = c
			c = Rol(b, 30)
			b = a ; a = t
		Next
    
		h0 += a
		h1 += b
		h2 += c
		h3 += d
		h4 += e
	Next
  
	Return (Hex(h0) + Hex(h1) + Hex(h2) + Hex(h3) + Hex(h4)).ToLower()

End
 
Function SHA256:String( in:String )
	
	Local h0:Int = $6A09E667, h1:Int = $BB67AE85, h2:Int = $3C6EF372, h3:Int = $A54FF53A
	Local h4:Int = $510E527F, h5:Int = $9B05688C, h6:Int = $1F83D9AB, h7:Int = $5BE0CD19
  
	Local k:Int[] = New Int[](
		$428A2F98, $71374491, $B5C0FBCF, $E9B5DBA5, $3956C25B, $59F111F1,
		$923F82A4, $AB1C5ED5, $D807AA98, $12835B01, $243185BE, $550C7DC3,
		$72BE5D74, $80DEB1FE, $9BDC06A7, $C19BF174, $E49B69C1, $EFBE4786,
		$0FC19DC6, $240CA1CC, $2DE92C6F, $4A7484AA, $5CB0A9DC, $76F988DA,
		$983E5152, $A831C66D, $B00327C8, $BF597FC7, $C6E00BF3, $D5A79147,
		$06CA6351, $14292967, $27B70A85, $2E1B2138, $4D2C6DFC, $53380D13,
		$650A7354, $766A0ABB, $81C2C92E, $92722C85, $A2BFE8A1, $A81A664B,
		$C24B8B70, $C76C51A3, $D192E819, $D6990624, $F40E3585, $106AA070,
		$19A4C116, $1E376C08, $2748774C, $34B0BCB5, $391C0CB3, $4ED8AA4A,
		$5B9CCA4F, $682E6FF3, $748F82EE, $78A5636F, $84C87814, $8CC70208,
		$90BEFFFA, $A4506CEB, $BEF9A3F7, $C67178F2)
 
	Local intCount:Int = (((in.Length + 8) Shr 6) + 1) Shl 4
	Local data:Int[] = New Int[intCount]
  
	For Local c:Int=0 Until in.Length
		data[c Shr 2] = (data[c Shr 2] Shl 8) | (in[c] & $FF)
	Next
	
	data[in.Length Shr 2] = ((data[in.Length Shr 2] Shl 8) | $80) Shl ((3 - (in.Length & 3)) Shl 3) 
	data[data.Length - 2] = (Long(in.Length) * 8) Shr 32
	data[data.Length - 1] = (Long(in.Length) * 8) & $FFFFFFFF
  
	For Local chunkStart:Int=0 Until intCount Step 16
		
		Local a:Int = h0, b:Int = h1, c:Int = h2, d:Int = h3, e:Int = h4, f:Int = h5, g:Int = h6, h:Int = h7
 
		Local w:=data.Slice(chunkStart,chunkStart+16).Resize(64)
    
		For Local i:Int=16 To 63
			w[i] = w[i - 16] + (Ror(w[i - 15], 7) ~ Ror(w[i - 15], 18) ~ ( UShr(w[i - 15],3) ))+
            w[i - 7] + (Ror(w[i - 2], 17) ~ Ror(w[i - 2], 19) ~ ( UShr(w[i - 2],10) ))
		Next
    
		For Local i:Int=0 To 63
			Local t0:Int = (Ror(a, 2) ~ Ror(a, 13) ~ Ror(a, 22)) + ((a & b) | (b & c) | (c & a))
			Local t1:Int = h + (Ror(e, 6) ~ Ror(e, 11) ~ Ror(e, 25)) + ((e & f) | (~e & g)) + k[i] + w[i]
      
			h = g ; g = f ; f = e ; e = d + t1
			d = c ; c = b ; b = a ;  a = t0 + t1  
		Next
    
		h0 += a ; h1 += b ; h2 += c ; h3 += d
		h4 += e ; h5 += f ; h6 += g ; h7 += h
	Next
  
	Return (Hex(h0) + Hex(h1) + Hex(h2) + Hex(h3) + Hex(h4) + Hex(h5) + Hex(h6) + Hex(h7)).ToLower()
	
End
 
